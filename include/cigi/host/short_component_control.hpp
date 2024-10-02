#pragma once

#include "general.hpp"
#include "component_control.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.5
    struct alignas(std::uint64_t) short_component_control
    {
        constexpr short_component_control() = default;
        constexpr short_component_control(const short_component_control&) = default;
        constexpr short_component_control(short_component_control&&) noexcept = default;
        constexpr ~short_component_control() = default;
        constexpr auto operator =(const short_component_control& other) -> short_component_control&
        {
            component_id = other.component_id;
            instance_id = other.instance_id;
            component_class = other.component_class;
            component_state = other.component_state;
            component_data[0] = other.component_data[0];
            component_data[1] = other.component_data[1];

            return *this;
        };

        static auto serialize(const short_component_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, short_component_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 5> packet_id;
        constant<u8, 16> packet_size;
        u16 component_id = 0;
        u16 instance_id = 0;
        component_control::component_class_t component_class : 6 = component_control::component_class_t::entity;
    private:
        u8 reserved_0 : 2 = 0;
    public:
        u8 component_state = 0;
        u32 component_data[2] = { 0, 0 };

        // offset is bytes
        auto set_u8(u8 data, bounded<u8, 0, 7> offset) -> void
        {
            component_data[offset / 4] &= ((0xFF << ((offset % 4) * 8)) ^ 0xFF'FF'FF'FF);
            component_data[offset / 4] |= ((data << ((offset % 4) * 8)) & 0xFF'FF'FF'FF);
        };
        // offset is bytes
        auto get_u8(bounded<u8, 0, 7> offset) -> u8
        {
            return (component_data[offset / 4] >> ((offset % 4) * 8)) & 0xFF;
        };

        // offset is bytes
        auto set_s8(s8 data, bounded<u8, 0, 7> offset) -> void
        {
            component_data[offset / 4] &= ((0xFF << ((offset % 4) * 8)) ^ 0xFF'FF'FF'FF);
            component_data[offset / 4] |= ((data << ((offset % 4) * 8)) & 0xFF'FF'FF'FF);
        };
        // offset is bytes
        auto get_s8(bounded<u8, 0, 7> offset) -> s8
        {
            return (component_data[offset / 4] >> ((offset % 4) * 8)) & 0xFF;
        };

        // offset is words
        auto set_u16(u16 data, bounded<u8, 0, 3> offset) -> void
        {
            component_data[offset / 2] &= ((0xFFFF << ((offset % 2) * 16)) ^ 0xFFFF'FFFF);
            component_data[offset / 2] |= ((data << ((offset % 2) * 16)) & 0xFFFF'FFFF);
        };
        // offset is words
        auto get_u16(bounded<u8, 0, 3> offset) -> u16
        {
            return (component_data[offset / 2] >> ((offset % 2) * 16)) & 0xFFFF;
        };

        // offset is words
        auto set_s16(s16 data, bounded<u8, 0, 3> offset) -> void
        {
            component_data[offset / 2] &= ((0xFFFF << ((offset % 2) * 16)) ^ 0xFFFF'FFFF);
            component_data[offset / 2] |= ((data << ((offset % 2) * 16)) & 0xFFFF'FFFF);
        };
        // offset is words
        auto get_s16(bounded<u8, 0, 3> offset) -> s16
        {
            return (component_data[offset / 2] >> ((offset % 2) * 16)) & 0xFFFF;
        };

        // offset is dwords
        auto set_u32(u32 data, bounded<u8, 0, 1> offset) -> void
        {
            component_data[offset] = data;
        };
        // offset is dwords
        auto get_u32(bounded<u8, 0, 1> offset) -> u32
        {
            return component_data[offset];
        };

        // offset is dwords
        auto set_s32(s32 data, bounded<u8, 0, 1> offset) -> void
        {
            component_data[offset] = data;
        };
        // offset is dwords
        auto get_s32(bounded<u8, 0, 1> offset) -> s32
        {
            return component_data[offset];
        };

        // offset is dwords
        auto set_f32(f32 data, bounded<u8, 0, 1> offset) -> void
        {
            component_data[offset] = std::bit_cast<u32>(data);
        };
        // offset is dwords
        auto get_f32(bounded<u8, 0, 1> offset) -> f32
        {
            return std::bit_cast<f32>(component_data[offset]);
        };

        auto set_u64(u64 data) -> void
        {
            component_data[0] = u32(data);
            component_data[1] = u32(data >> 32);
        };
        // offset is qwords
        auto get_u64() -> u64
        {
            return component_data[0] | (u64(component_data[1]) << 32);
        };

        // offset is qwords
        auto set_s64(s64 data) -> void
        {
            component_data[0] = u32(data);
            component_data[1] = u32(data >> 32);
        };
        // offset is qwords
        auto get_s64() -> s64
        {
            return component_data[0] | (s64(component_data[1]) << 32);
        };

        // offset is qwords
        auto set_f64(f64 data) -> void
        {
            set_u64(std::bit_cast<u64>(data));
        };
        // offset is qwords
        auto get_f64() -> f64
        {
            return std::bit_cast<f64>(get_u64());
        };

        // offset is bits
        auto set_bit(bool data, bounded<u8, 0, 63> offset) -> void
        {
            component_data[offset / 32] &= ((0b1 << (offset % 32)) ^ 0b1111'1111'1111'1111'1111'1111'1111'1111);
            component_data[offset / 32] |= ((data << (offset % 32)) & 0b1111'1111'1111'1111'1111'1111'1111'1111);
        };
        // offset is bits
        auto get_bit(bounded<u8, 0, 63> offset) -> bool
        {
            return (component_data[offset / 32] >> (offset % 32)) & 0b1;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::short_component_control& value) -> std::ostream&
{
    o << "short_component_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tcomponent_id: " << value.component_id;
    o << "\n\tinstance_id: " << value.instance_id;
    o << "\n\tcomponent_class: " << value.component_class;
    o << "\n\tcomponent_state: " << (int)value.component_state;
    o << "\n\tcomponent_data: ";
    o << "\n\t\t0: " << value.component_data[0];
    o << "\n\t\t1: " << value.component_data[1];

    return o << "\n}";
}