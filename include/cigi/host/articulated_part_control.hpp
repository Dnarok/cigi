#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.6
    struct alignas(std::uint64_t) articulated_part_control
    {
        constexpr articulated_part_control() = default;
        constexpr articulated_part_control(const articulated_part_control&) = default;
        constexpr articulated_part_control(articulated_part_control&&) noexcept = default;
        constexpr ~articulated_part_control() = default;
        constexpr auto operator =(const articulated_part_control& other) -> articulated_part_control&
        {
            entity_id = other.entity_id;
            articulated_part_id = other.articulated_part_id;
            articulated_part_enable = other.articulated_part_enable;
            x_offset_enable = other.x_offset_enable;
            y_offset_enable = other.y_offset_enable;
            z_offset_enable = other.z_offset_enable;
            roll_enable = other.roll_enable;
            pitch_enable = other.pitch_enable;
            yaw_enable = other.yaw_enable;
            x_offset = other.x_offset;
            y_offset = other.y_offset;
            z_offset = other.z_offset;
            roll = other.roll;
            pitch = other.pitch;
            yaw = other.yaw;

            return *this;
        };

        static auto serialize(const articulated_part_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, articulated_part_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 6> packet_id;
        constant<u8, 32> packet_size;
        u16 entity_id = 0;
        u8 articulated_part_id = 0;
        enable_t articulated_part_enable : 1 = enable_t::disabled;
        enable_t x_offset_enable : 1 = enable_t::disabled;
        enable_t y_offset_enable : 1 = enable_t::disabled;
        enable_t z_offset_enable : 1 = enable_t::disabled;
        enable_t roll_enable : 1 = enable_t::disabled;
        enable_t pitch_enable : 1 = enable_t::disabled;
        enable_t yaw_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_0 : 1 = 0;
        constant<u16, 0> reserved_1;
    public:
        f32 x_offset = 0.f;
        f32 y_offset = 0.f;
        f32 z_offset = 0.f;
        bounded<f32, -180.f, 180.f> roll = 0.f;
        bounded<f32, -90.f, 90.f> pitch = 0.f;
        bounded<f32, 0.f, 360.f> yaw = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::articulated_part_control& value) -> std::ostream&
{
    o << "articulated_part_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tarticulated_part_id: " << (int)value.articulated_part_id;
    o << "\n\tarticulated_part_enable: " << value.articulated_part_enable;
    o << "\n\tx_offset_enable: " << value.x_offset_enable;
    o << "\n\ty_offset_enable: " << value.y_offset_enable;
    o << "\n\tz_offset_enable: " << value.z_offset_enable;
    o << "\n\troll_enable: " << value.roll_enable;
    o << "\n\tpitch_enable: " << value.pitch_enable;
    o << "\n\tyaw_enable: " << value.yaw_enable;
    o << "\n\tx_offset: " << value.x_offset;
    o << "\n\ty_offset: " << value.y_offset;
    o << "\n\tz_offset: " << value.z_offset;
    o << "\n\troll: " << value.roll;
    o << "\n\tpitch: " << value.pitch;
    o << "\n\tyaw: " << value.yaw;

    return o << "\n}";
}