#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.18
    struct alignas(std::uint64_t) motion_tracker_control
    {
        enum class view_t : u8
        {
            view = 0,
            view_group = 1,
        };

        constexpr motion_tracker_control() = default;
        constexpr motion_tracker_control(const motion_tracker_control&) = default;
        constexpr motion_tracker_control(motion_tracker_control&&) noexcept = default;
        constexpr ~motion_tracker_control() = default;
        constexpr auto operator =(const motion_tracker_control& other) -> motion_tracker_control&
        {
            view_id = other.view_id;
            tracker_id = other.tracker_id;
            tracker_enable = other.tracker_enable;
            boresight_enable = other.boresight_enable;
            x_enable = other.x_enable;
            y_enable = other.y_enable;
            z_enable = other.z_enable;
            roll_enable = other.roll_enable;
            pitch_enable = other.pitch_enable;
            yaw_enable = other.yaw_enable;
            view_select = other.view_select;

            return *this;
        };

        static auto serialize(const motion_tracker_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, motion_tracker_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 18> packet_id;
        constant<u8, 8> packet_size;
        union
        {
            u16 view_id = 0;
            u16 view_group_id;
        };
        u8 tracker_id = 0;
        enable_t tracker_enable : 1 = enable_t::disabled;
        enable_t boresight_enable : 1 = enable_t::disabled;
        enable_t x_enable : 1 = enable_t::enabled;
        enable_t y_enable : 1 = enable_t::enabled;
        enable_t z_enable : 1 = enable_t::enabled;
        enable_t roll_enable : 1 = enable_t::enabled;
        enable_t pitch_enable : 1 = enable_t::enabled;
        enable_t yaw_enable : 1 = enable_t::enabled;
        view_t view_select : 1 = view_t::view;
    private:
        u8 reserved_0 : 7 = 0;
        constant<u8, 0> reserved_1;
    };
};

inline auto operator <<(std::ostream& o, const cigi::motion_tracker_control::view_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::motion_tracker_control::view_t;
    case view:
        return o << "view";
    case view_group:
        return o << "view group";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::motion_tracker_control& value) -> std::ostream&
{
    o << "motion_tracker_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tview_id: " << value.view_id;
    o << "\n\ttracker_id: " << (int)value.tracker_id;
    o << "\n\ttracker_enable: " << value.tracker_enable;
    o << "\n\tboresight_enable: " << value.boresight_enable;
    o << "\n\tx_enable: " << value.x_enable;
    o << "\n\ty_enable: " << value.y_enable;
    o << "\n\tz_enable: " << value.z_enable;
    o << "\n\troll_enable: " << value.roll_enable;
    o << "\n\tpitch_enable: " << value.pitch_enable;
    o << "\n\tyaw_enable: " << value.yaw_enable;
    o << "\n\tview_select: " << value.view_select;

    return o << "\n}";
};