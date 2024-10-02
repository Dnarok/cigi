#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.4
    struct alignas(std::uint64_t) component_control
    {
        enum class component_class_t : u8
        {
            entity = 0,
            view = 1,
            view_group = 2,
            sensor = 3,
            regional_sea_surface = 4,
            regional_terrain_surface = 5,
            regional_layered_weather = 6,
            global_sea_surface = 7,
            global_terrain_surface = 8,
            global_layered_weather = 9,
            atmosphere = 10,
            celestial_sphere = 11,
            event = 12,
            system = 13,
            symbol_surface = 14,
            symbol = 15,
        };

        constexpr component_control() = default;
        constexpr component_control(const component_control&) = default;
        constexpr component_control(component_control&&) noexcept = default;
        constexpr ~component_control() = default;
        constexpr auto operator =(const component_control& other) -> component_control&
        {
            component_id = other.component_id;
            instance_id = other.instance_id;
            component_class = other.component_class;
            component_state = other.component_state;
            component_data[0] = other.component_data[0];
            component_data[1] = other.component_data[1];
            component_data[2] = other.component_data[2];
            component_data[3] = other.component_data[3];
            component_data[4] = other.component_data[4];
            component_data[5] = other.component_data[5];

            return *this;
        };

        static auto serialize(const component_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, component_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 4> packet_id;
        constant<u8, 32> packet_size;
        u16 component_id = 0;
        u16 instance_id = 0;
        component_class_t component_class : 6 = component_class_t::entity;
    private:
        u8 reserved_0 : 2 = 0;
    public:
        u8 component_state = 0;
        u32 component_data[6] = { 0, 0, 0, 0, 0, 0 };

        // offset is bytes
        auto set_u8(u8 data, bounded<u8, 0, 23> offset) -> void
        {
            component_data[offset / 4] &= ((0xFF << ((offset % 4) * 8)) ^ 0xFF'FF'FF'FF);
            component_data[offset / 4] |= ((data << ((offset % 4) * 8)) & 0xFF'FF'FF'FF);
        };
        // offset is bytes
        auto get_u8(bounded<u8, 0, 23> offset) -> u8
        {
            return (component_data[offset / 4] >> ((offset % 4) * 8)) & 0xFF;
        };

        // offset is bytes
        auto set_s8(s8 data, bounded<u8, 0, 23> offset) -> void
        {
            component_data[offset / 4] &= ((0xFF << ((offset % 4) * 8)) ^ 0xFF'FF'FF'FF);
            component_data[offset / 4] |= ((data << ((offset % 4) * 8)) & 0xFF'FF'FF'FF);
        };
        // offset is bytes
        auto get_s8(bounded<u8, 0, 23> offset) -> s8
        {
            return (component_data[offset / 4] >> ((offset % 4) * 8)) & 0xFF;
        };

        // offset is words
        auto set_u16(u16 data, bounded<u8, 0, 11> offset) -> void
        {
            component_data[offset / 2] &= ((0xFFFF << ((offset % 2) * 16)) ^ 0xFFFF'FFFF);
            component_data[offset / 2] |= ((data << ((offset % 2) * 16)) & 0xFFFF'FFFF);
        };
        // offset is words
        auto get_u16(bounded<u8, 0, 11> offset) -> u16
        {
            return (component_data[offset / 2] >> ((offset % 2) * 16)) & 0xFFFF;
        };

        // offset is words
        auto set_s16(s16 data, bounded<u8, 0, 11> offset) -> void
        {
            component_data[offset / 2] &= ((0xFFFF << ((offset % 2) * 16)) ^ 0xFFFF'FFFF);
            component_data[offset / 2] |= ((data << ((offset % 2) * 16)) & 0xFFFF'FFFF);
        };
        // offset is words
        auto get_s16(bounded<u8, 0, 11> offset) -> s16
        {
            return (component_data[offset / 2] >> ((offset % 2) * 16)) & 0xFFFF;
        };

        // offset is dwords
        auto set_u32(u32 data, bounded<u8, 0, 5> offset) -> void
        {
            component_data[offset] = data;
        };
        // offset is dwords
        auto get_u32(bounded<u8, 0, 5> offset) -> u32
        {
            return component_data[offset];
        };

        // offset is dwords
        auto set_s32(s32 data, bounded<u8, 0, 5> offset) -> void
        {
            component_data[offset] = data;
        };
        // offset is dwords
        auto get_s32(bounded<u8, 0, 5> offset) -> s32
        {
            return component_data[offset];
        };

        // offset is dwords
        auto set_f32(f32 data, bounded<u8, 0, 5> offset) -> void
        {
            component_data[offset] = std::bit_cast<u32>(data);
        };
        // offset is dwords
        auto get_f32(bounded<u8, 0, 5> offset) -> f32
        {
            return std::bit_cast<f32>(component_data[offset]);
        };

        // offset is qwords
        auto set_u64(u64 data, bounded<u8, 0, 2> offset) -> void
        {
            component_data[offset * 2]     = u32(data);
            component_data[offset * 2 + 1] = u32(data >> 32);
        };
        // offset is qwords
        auto get_u64(bounded<u8, 0, 2> offset) -> u64
        {
            return component_data[offset * 2] | (u64(component_data[offset * 2 + 1]) << 32);
        };

        // offset is qwords
        auto set_s64(s64 data, bounded<u8, 0, 2> offset) -> void
        {
            component_data[offset * 2]     = u32(data);
            component_data[offset * 2 + 1] = u32(data >> 32);
        };
        // offset is qwords
        auto get_s64(bounded<u8, 0, 2> offset) -> s64
        {
            return component_data[offset * 2] | (s64(component_data[offset * 2 + 1]) << 32);
        };

        // offset is qwords
        auto set_f64(f64 data, bounded<u8, 0, 2> offset) -> void
        {
            set_u64(std::bit_cast<u64>(data), offset);
        };
        // offset is qwords
        auto get_f64(bounded<u8, 0, 2> offset) -> f64
        {
            return std::bit_cast<f64>(get_u64(offset));
        };

        // offset is bits
        auto set_bit(bool data, bounded<u8, 0, 191> offset) -> void
        {
            component_data[offset / 32] &= ((0b1 << (offset % 32)) ^ 0b1111'1111'1111'1111'1111'1111'1111'1111);
            component_data[offset / 32] |= ((data << (offset % 32)) & 0b1111'1111'1111'1111'1111'1111'1111'1111);
        };
        // offset is bits
        auto get_bit(bounded<u8, 0, 191> offset) -> bool
        {
            return (component_data[offset / 32] >> (offset % 32)) & 0b1;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::component_control::component_class_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::component_control::component_class_t;
    case entity:
        return o << "entity";
    case view:
        return o << "view";
    case view_group:
        return o << "view group";
    case sensor:
        return o << "sensor";
    case regional_sea_surface:
        return o << "regional sea surface";
    case regional_terrain_surface:
        return o << "regional terrain surface";
    case regional_layered_weather:
        return o << "regional layered weather";
    case global_sea_surface:
        return o << "global sea surface";
    case global_terrain_surface:
        return o << "global terrain surface";
    case global_layered_weather:
        return o << "global layered weather";
    case atmosphere:
        return o << "atmosphere";
    case celestial_sphere:
        return o << "celestial sphere";
    case event:
        return o << "event";
    case system:
        return o << "system";
    case symbol_surface:
        return o << "symbol surface";
    case symbol:
        return o << "symbol";
    default:
        return o << "reserved(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::component_control& value) -> std::ostream&
{
    o << "component_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tcomponent_id: " << value.component_id;
    o << "\n\tinstance_id: " << value.instance_id;
    o << "\n\tcomponent_class: " << value.component_class;
    o << "\n\tcomponent_state: " << (int)value.component_state;
    o << "\n\tcomponent_data: ";
    o << "\n\t\t0: " << value.component_data[0];
    o << "\n\t\t1: " << value.component_data[1];
    o << "\n\t\t2: " << value.component_data[2];
    o << "\n\t\t3: " << value.component_data[3];
    o << "\n\t\t4: " << value.component_data[4];
    o << "\n\t\t5: " << value.component_data[5];

    return o << "\n}";
}