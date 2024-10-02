#pragma once

#include "general.hpp"
#include "socket.hpp"

#include <map>
#include <future>
#include <optional>

namespace cigi
{
    struct session_network
    {
        send_socket send;
        receive_socket receive;
        std::vector<serialized_data> outgoing;
        std::map<u8, std::vector<serialized_data>> incoming;

        auto connect(std::string_view ip, std::uint16_t send_port, std::uint16_t receive_port, std::string_view receive_device = "")
        {
            send.connect(ip, send_port);
            receive.connect("", receive_port, receive_device);
        };

        template <cigi_packet T>
        auto write(const T& packet) -> serialized_data::errors
        {
            auto [data, errors] = T::serialize(packet);
            if (errors == serialized_data::errors::none)
            {
                outgoing.push_back(data);
            }
            return errors;
        };
        auto flush() -> void
        {
            std::vector<std::byte> buffer;
            buffer.reserve(outgoing.size() * 8);

            for (auto& data : outgoing)
            {
                auto start = data.start_pointer();
                std::copy(start, start + data.size(), std::back_inserter(buffer));
            }

            send.send_bytes(buffer);
            send.flush();
            outgoing.clear();
        };

        // blocks until packets found or timeout.
        // consumes any packets found before returning. 
        // timeout of 0 is non-blocking, just an immediate poll.
        auto poll(std::chrono::microseconds timeout) -> bool
        {
            if (receive.select(timeout))
            {
                if (int bytes = receive.bytes_available(); bytes > 0)
                {
                    std::vector<std::byte> data;
                    receive.read_bytes(bytes, data);

                    std::size_t offset = 0;
                    while (offset + 1 < bytes && u8(data[offset + 1]) != 0 && offset + u8(data[offset + 1]) <= bytes)
                    {
                        serialized_data serial{ data.data() + offset, std::size_t(data[offset + 1]) };
                        u8 pid = serial.packet_id();
                        incoming[pid].push_back(serial);
                        offset += serial.packet_size();
                    }

                    return true;
                }
            }

            return false;
        };
        template <cigi_packet T>
        auto read() -> std::optional<T>
        {
            auto find = incoming.find(decltype(T::packet_id)::value);
            if (find != incoming.end())
            {
                if (!find->second.empty())
                {
                    T packet;
                    auto errors = T::deserialize(find->second.front(), packet);
                    find->second.erase(find->second.begin());
                    if (errors == serialized_data::errors::none)
                    {
                        return packet;
                    }
                }
            }

            return std::nullopt;
        };
        template <cigi_packet T>
        auto read_all() -> std::vector<T>
        {
            std::vector<T> out;

            auto find = incoming.find(decltype(T::packet_id)::value);
            if (find != incoming.end())
            {
                while (!find->second.empty())
                {
                    T packet;
                    auto errors = T::deserialize(find->second.front(), packet);
                    find->second.erase(find->second.begin());
                    if (errors == serialized_data::errors::none)
                    {
                        out.push_back(packet);
                    }
                }
            }
            
            return out;
        };
        template <cigi_packet T>
        auto read_async(std::launch launch = std::launch::deferred) -> std::future<T>
        {
            return std::async(launch, [&]()
            {
                using namespace std::chrono_literals;
                while (true)
                {
                    if (poll(1'000us))
                    {
                        if (auto packet = this->read<T>(); packet.has_value())
                        {
                            return packet.value();
                        }
                    }
                }
            });
        };
    };
};