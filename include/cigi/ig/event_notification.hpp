#pragma once

#include "general.hpp"
#include <bit>

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.16
    struct alignas(std::uint64_t) event_notification
    {
        constexpr event_notification() = default;
        constexpr event_notification(const event_notification&) = default;
        constexpr event_notification(event_notification&&) noexcept = default;
        constexpr ~event_notification() = default;
        constexpr auto operator =(const event_notification& other) -> event_notification&
        {
            event_id = other.event_id;
            event_data[0] = other.event_data[0];
            event_data[1] = other.event_data[1];
            event_data[2] = other.event_data[2];

            return *this;
        };

        static auto serialize(const event_notification& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, event_notification& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 116> packet_id;
        constant<u8, 16> packet_size;
        u16 event_id = 0;
        u32 event_data[3] = { 0, 0, 0 };

        // offset is bytes
        auto set_u8(u8 data, bounded<u8, 0, 11> offset) -> void
        {
            event_data[offset / 4] &= ((0xFF << ((offset % 4) * 8)) ^ 0xFF'FF'FF'FF);
            event_data[offset / 4] |= ((data << ((offset % 4) * 8)) & 0xFF'FF'FF'FF);
        };
        // offset is bytes
        auto get_u8(bounded<u8, 0, 11> offset) -> u8
        {
            return (event_data[offset / 4] >> ((offset % 4) * 8)) & 0xFF;
        };
        // offset is bytes
        auto set_s8(s8 data, bounded<u8, 0, 11> offset) -> void
        {
            event_data[offset / 4] &= ((0xFF << ((offset % 4) * 8)) ^ 0xFF'FF'FF'FF);
            event_data[offset / 4] |= ((data << ((offset % 4) * 8)) & 0xFF'FF'FF'FF);
        };
        // offset is bytes
        auto get_s8(bounded<u8, 0, 11> offset) -> s8
        {
            return (event_data[offset / 4] >> ((offset % 4) * 8)) & 0xFF;
        };

        // offset is words
        auto set_u16(u16 data, bounded<u8, 0, 5> offset) -> void
        {
            event_data[offset / 2] &= ((0xFFFF << ((offset % 2) * 16)) ^ 0xFFFF'FFFF);
            event_data[offset / 2] |= ((data << ((offset % 2) * 16)) & 0xFFFF'FFFF);
        };
        // offset is words
        auto get_u16(bounded<u8, 0, 5> offset) -> u16
        {
            return (event_data[offset / 2] >> ((offset % 2) * 16)) & 0xFFFF;
        };
        // offset is words
        auto set_s16(s16 data, bounded<u8, 0, 5> offset) -> void
        {
            event_data[offset / 2] &= ((0xFFFF << ((offset % 2) * 16)) ^ 0xFFFF'FFFF);
            event_data[offset / 2] |= ((data << ((offset % 2) * 16)) & 0xFFFF'FFFF);
        };
        // offset is words
        auto get_s16(bounded<u8, 0, 5> offset) -> s16
        {
            return (event_data[offset / 2] >> ((offset % 2) * 16)) & 0xFFFF;
        };

        // offset is dwords
        auto set_u32(u32 data, bounded<u8, 0, 2> offset) -> void
        {
            event_data[offset] = data;
        };
        // offset is dwords
        auto get_u32(bounded<u8, 0, 2> offset) -> u32
        {
            return event_data[offset];
        };
        // offset is dwords
        auto set_s32(s32 data, bounded<u8, 0, 2> offset) -> void
        {
            event_data[offset] = data;
        };
        // offset is dwords
        auto get_s32(bounded<u8, 0, 2> offset) -> s32
        {
            return event_data[offset];
        };
        // offset is dwords
        auto set_f32(f32 data, bounded<u8, 0, 2> offset) -> void
        {
            event_data[offset] = std::bit_cast<u32>(data);
        };
        // offset is dwords
        auto get_f32(bounded<u8, 0, 2> offset) -> f32
        {
            return std::bit_cast<f32>(event_data[offset]);
        };

        // offset is qwords
        auto set_u64(u64 data, bounded<u8, 0, 1> offset) -> void
        {
            event_data[offset]     = u32(data);
            event_data[offset + 1] = u32(data >> 32);
        };
        // offset is qwords
        auto get_u64(bounded<u8, 0, 1> offset) -> u64
        {
            return event_data[offset] | (u64(event_data[offset + 1]) << 32);
        };
        // offset is qwords
        auto set_s64(s64 data, bounded<u8, 0, 1> offset) -> void
        {
            event_data[offset]     = u32(data);
            event_data[offset + 1] = u32(data >> 32);
        };
        // offset is qwords
        auto get_s64(bounded<u8, 0, 1> offset) -> s64
        {
            return event_data[offset] | (s64(event_data[offset + 1]) << 32);
        };
        // offset is qwords
        auto set_f64(f64 data, bounded<u8, 0, 1> offset) -> void
        {
            set_u64(std::bit_cast<u64>(data), offset);
        };
        // offset is qwords
        auto get_f64(bounded<u8, 0, 1> offset) -> f64
        {
            return std::bit_cast<f64>(get_u64(offset));
        };

        // offset is bits
        auto set_bit(bool data, bounded<u8, 0, 95> offset) -> void
        {
            event_data[offset / 32] &= ((0b1 << (offset % 32)) ^ 0b1111'1111'1111'1111'1111'1111'1111'1111);
            event_data[offset / 32] |= ((data << (offset % 32)) & 0b1111'1111'1111'1111'1111'1111'1111'1111);
        };
        // offset is bits
        auto get_bit(bounded<u8, 0, 95> offset) -> bool
        {
            return (event_data[offset / 32] >> (offset % 32)) & 0b1;
        };
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::event_notification& value) -> ostream&
{
    o << "event_notification {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tevent_id: " << value.event_id;
    o << "\n\tevent_data: ";
    o << "\n\t\t0: " << value.event_data[0];
    o << "\n\t\t1: " << value.event_data[1];
    o << "\n\t\t2: " << value.event_data[2];

    return o << "\n}";
};