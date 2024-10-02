#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.16
    struct alignas(std::uint64_t) view_control
    {
        constexpr view_control() = default;
        constexpr view_control(const view_control&) = default;
        constexpr view_control(view_control&&) noexcept = default;
        constexpr ~view_control() = default;
        constexpr auto operator =(const view_control& other) -> view_control&
        {
            view_id = other.view_id;
            group_id = other.group_id;
            x_offset_enable = other.x_offset_enable;
            y_offset_enable = other.y_offset_enable;
            z_offset_enable = other.z_offset_enable;
            roll_enable = other.roll_enable;
            pitch_enable = other.pitch_enable;
            yaw_enable = other.yaw_enable;
            entity_id = other.entity_id;
            x_offset = other.x_offset;
            y_offset = other.y_offset;
            z_offset = other.z_offset;
            roll = other.roll;
            pitch = other.pitch;
            yaw = other.yaw;

            return *this;
        };

        static auto serialize(const view_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, view_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 16> packet_id;
        constant<u8, 32> packet_size;
        u16 view_id = 0;
        u8 group_id = 0;
        enable_t x_offset_enable : 1 = enable_t::disabled;
        enable_t y_offset_enable : 1 = enable_t::disabled;
        enable_t z_offset_enable : 1 = enable_t::disabled;
        enable_t roll_enable : 1 = enable_t::disabled;
        enable_t pitch_enable : 1 = enable_t::disabled;
        enable_t yaw_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_0 : 2 = 0;
    public:
        u16 entity_id = 0;
        f32 x_offset = 0;
        f32 y_offset = 0;
        f32 z_offset = 0;
        bounded<f32, -180.f, 180.f> roll = 0.f;
        bounded<f32, -90.f, 90.f> pitch = 0.f;
        bounded<f32, 0.f, 360.f> yaw = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::view_control& value) -> std::ostream&
{
    o << "view_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tview_id: " << value.view_id;
    o << "\n\tgroup_id: " << (int)value.group_id;
    o << "\n\tx_offset_enable: " << value.x_offset_enable;
    o << "\n\ty_offset_enable: " << value.y_offset_enable;
    o << "\n\tz_offset_enable: " << value.z_offset_enable;
    o << "\n\troll_enable: " << value.roll_enable;
    o << "\n\tpitch_enable: " << value.pitch_enable;
    o << "\n\tyaw_enable: " << value.yaw_enable;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tx_offset: " << value.x_offset;
    o << "\n\ty_offset: " << value.y_offset;
    o << "\n\tz_offset: " << value.z_offset;
    o << "\n\troll: " << value.roll;
    o << "\n\tpitch: " << value.pitch;
    o << "\n\tyaw: " << value.yaw;

    return o << "\n}";
};