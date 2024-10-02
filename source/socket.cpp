#include "socket.hpp"

#ifdef _WIN32
#   include <WinSock2.h>
#   include <WS2tcpip.h>
#   define CLOSE_SOCKET ::closesocket
#   define IOCTL_SOCKET ::ioctlsocket
#else
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <sys/ioctl.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#   include <netdb.h>
#   include <unistd.h>
#   include <errno.h>
#   include <sys.h>
#   include <cstring>
#   define CLOSE_SOCKET ::close
#   define IOCTL_SOCKET ::ioctl
using SOCKET = int;
constexpr int INVALID_SOCKET = -1;
#endif

#include <iostream>

namespace
{
    constexpr std::size_t mtu_size = 1432;

    struct socket_initializer
    {
        socket_initializer()
        {
        #ifdef _WIN32
            WSADATA wsa_data;
            if (WSAStartup(MAKEWORD(2, 2), &wsa_data) < 0)
            {
                std::cout << "Failed WSAStartup.\n";
            }
        #endif
        };
        ~socket_initializer()
        {
        #ifdef _WIN32
            if (WSACleanup() < 0)
            {
                std::cout << "Failed WSACleanup.\n";
            }
        #endif
        };
    };

    auto initialize_sockets() -> void
    {
    #ifdef _WIN32
        static socket_initializer init;
    #endif
    };

    auto to_ipv4(const std::string& address, std::uint32_t& ipv4) -> bool
    {
        struct addrinfo hints { 0 };
        hints.ai_family = AF_INET;

        struct addrinfo* info = nullptr;
        bool result = false;
        if (getaddrinfo(address.c_str(), nullptr, &hints, &info) == 0)
        {
            for (struct addrinfo* next = info; next != nullptr && !result; next = next->ai_next)
            {
                switch (next->ai_family)
                {
                case AF_INET:
                    ipv4 = ntohl(((struct sockaddr_in*)info->ai_addr)->sin_addr.s_addr);
                    result = true;
                    break;
                }
            }

            freeaddrinfo(info);
        }

        return result;
    };

    auto is_multicast(const std::string& address, std::uint32_t& ipv4) -> bool
    {
        if (!to_ipv4(address, ipv4))
        {
            return false;
        }

        std::uint8_t octet = std::uint8_t(ipv4 >> 24);
        return octet >= 224 && octet <= 239;
    };
};

namespace cigi
{
    struct send_socket::send_socket_impl
    {
        SOCKET                  socket = INVALID_SOCKET;
        std::vector<std::byte>  cache = {};
        std::atomic_uint64_t    packets_sent = 0;
        std::atomic_uint64_t    bytes_sent = 0;

        auto connect(std::string_view ip, std::uint16_t port) -> void
        {
            initialize_sockets();
            socket = ::socket(AF_INET, SOCK_DGRAM, 0);

            int enable = 1;
            if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(int)) < 0)
            {
                std::cout << "send_socket: Failed to set SO_REUSEADDR.\n";
            }

            sockaddr_in socket_address{ 0 };
            socket_address.sin_family = AF_INET;
            socket_address.sin_port = htons(port);

            std::uint32_t ipv4;
            if (!to_ipv4(std::string{ ip }, ipv4))
            {
                std::cout << "send_socket: Did not receive IPv4 IP: " << ip << ":" << port << ".\n";
            }
            socket_address.sin_addr.s_addr = htonl(ipv4);

            if (::connect(socket, (const sockaddr*)&socket_address, sizeof(sockaddr_in)) < 0)
            {
                std::cout << "send_socket: Failed to connect to " << ip << ":" << port << ".\n";
            }
        };
        auto disconnect() -> void
        {
            if (socket != INVALID_SOCKET)
            {
                CLOSE_SOCKET(socket);
            }
        };
        auto send_bytes(std::span<std::byte> bytes) -> void
        {
            std::size_t cached_size = cache.size();
            std::size_t new_cache_size = cached_size + bytes.size();
            if (new_cache_size < mtu_size)
            {
                cache.resize(new_cache_size);
                std::copy(bytes.data(), bytes.data() + bytes.size(), cache.data() + cached_size);
            }
            else
            {
                flush();
                cache.resize(bytes.size());
                std::copy(bytes.data(), bytes.data() + bytes.size(), cache.data());
            }
        };
        auto flush() -> void
        {
            if (cache.empty())
            {
                return;
            }

            if (socket != INVALID_SOCKET)
            {
                ::send(socket, (char*)cache.data(), cache.size(), 0);
            }

            packets_sent.fetch_add(1);
            bytes_sent.fetch_add(cache.size());

            cache.clear();
        };
    };

    send_socket::send_socket() :
        impl{ new send_socket_impl }
    {};
    send_socket::~send_socket()
    {
        disconnect();
    };
    auto send_socket::connect(std::string_view ip, std::uint16_t port) -> void
    {
        impl->disconnect();
        impl->connect(ip, port);
    };
    auto send_socket::disconnect() -> void
    {
        impl->disconnect();
    };
    auto send_socket::send_bytes(std::span<std::byte> bytes) -> void
    {
        impl->send_bytes(bytes);
    };
    auto send_socket::flush() -> void
    {
        impl->flush();
    };
    auto send_socket::packets_sent() const -> std::uint64_t
    {
        return impl->packets_sent;
    };
    auto send_socket::bytes_sent() const -> std::uint64_t
    {
        return impl->bytes_sent;
    };

    struct receive_socket::receive_socket_impl
    {
        SOCKET socket = INVALID_SOCKET;

        auto connect(std::string_view ip, std::uint16_t port, std::string_view device) -> void
        {
            initialize_sockets();
            socket = ::socket(AF_INET, SOCK_DGRAM, 0);

            int enable = 1;
            if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(int)) < 0)
            {
                std::cout << "receive_socket: Failed to set SO_REUSEADDR.\n";
            }

            sockaddr_in socket_address{ 0 };
            socket_address.sin_family = AF_INET;
            socket_address.sin_port = htons(port);
            socket_address.sin_addr.s_addr = htonl(INADDR_ANY);

            if (::bind(socket, (const sockaddr*)&socket_address, sizeof(sockaddr_in)) < 0)
            {
                std::cout << "receive_socket: Failed to bind to port " << port << ".\n";
            }

            std::uint32_t ip_address = 0;
            if (is_multicast(std::string{ ip }, ip_address))
            {
                struct ip_mreq mreq;
                if (!device.empty())
                {
                    std::uint32_t device_address = 0;
                    if (!to_ipv4(std::string{ device }, device_address))
                    {
                        std::cout << "receive_socket: Did not receive IPv4 device: " << device << ".\n";
                    }

                    mreq.imr_interface.s_addr = htonl(device_address);
                }
                else
                {
                    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
                }
                mreq.imr_multiaddr.s_addr = htonl(ip_address);

                if (::setsockopt(socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0)
                {
                    std::cout << "receive_socket: Failed to set IP_ADD_MEMBERSHIP.\n";
                }
            }
        };
        auto disconnect() -> void
        {
            if (socket != INVALID_SOCKET)
            {
                CLOSE_SOCKET(socket);
            }
        };
        auto bytes_available() const -> int
        {
            if (socket == INVALID_SOCKET)
            {
                return -1;
            }

            u_long out;
            if (IOCTL_SOCKET(socket, FIONREAD, &out) < 0)
            {
                return -1;
            }

            return int(out);
        };
        auto read_bytes(int size, std::vector<std::byte>& data) const -> bool
        {
            data.clear();

            if (socket == INVALID_SOCKET)
            {
                return false;
            }

            std::size_t bytes = 0;
            if (size <= 0)
            {
                return false;
            }

            data.resize(size);
            bytes = ::recv(socket, (char*)data.data(), size, 0);

            if (bytes < 0)
            {
                std::cout << "receive_socket: Failed recv.\n";
            }
            else if (bytes == 0)
            {
                std::cout << "receive_socket: Peer shutdown.\n";
            }
            else if (data.size() != bytes)
            {
                data.resize(bytes);
            }

            return bytes > 0;
        };
        auto select(std::chrono::microseconds timeout_us) const -> bool
        {
            fd_set sockets{ 0 };
            FD_SET(socket, &sockets);

            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = timeout_us.count();

            int socket_count = ::select(socket + 1, &sockets, nullptr, nullptr, &timeout);
            return socket_count > 0;
        };
    };

    receive_socket::receive_socket() :
        impl{ new receive_socket_impl }
    {};
    receive_socket::~receive_socket()
    {
        disconnect();
    };
    auto receive_socket::connect(std::string_view ip, std::uint16_t port, std::string_view device) -> void
    {
        impl->disconnect();
        impl->connect(ip, port, device);
    };
    auto receive_socket::disconnect() -> void
    {
        impl->disconnect();
    };
    auto receive_socket::bytes_available() const -> int
    {
        return impl->bytes_available();
    };
    auto receive_socket::read_bytes(int size, std::vector<std::byte>& data) const -> bool
    {
        return impl->read_bytes(size, data);
    };
    auto receive_socket::select(std::chrono::microseconds timeout) const -> bool
    {
        return impl->select(timeout);
    };
};