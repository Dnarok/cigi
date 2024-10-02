#pragma once

#include <string_view>
#include <cstdint>
#include <span>
#include <chrono>
#include <memory>
#include <vector>

namespace cigi
{
    struct send_socket
    {
        send_socket();
        ~send_socket();

        auto connect(std::string_view ip, std::uint16_t port) -> void;
        auto disconnect() -> void;
        auto send_bytes(std::span<std::byte> bytes) -> void;
        auto flush() -> void;
        
        auto packets_sent() const -> std::uint64_t;
        auto bytes_sent() const -> std::uint64_t;

    private:
        struct send_socket_impl;
        std::unique_ptr<send_socket_impl> impl;
    };

    struct receive_socket
    {
        receive_socket();
        ~receive_socket();

        auto connect(std::string_view ip, std::uint16_t port, std::string_view device) -> void;
        auto disconnect() -> void;
        auto bytes_available() const -> int;
        auto read_bytes(int size, std::vector<std::byte>& data) const -> bool;
        auto select(std::chrono::microseconds timeout) const -> bool;

    private:
        struct receive_socket_impl;
        std::unique_ptr<receive_socket_impl> impl;
    };
};