#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.2
    struct entity_control
    {
        enum class ground_ocean_clamp_t : u8
        {
            no_clamp = 0,
            non_conformal = 1,
            conformal = 2,
        };
        enum class animation_direction_t : u8
        {
            forward = 0,
            backward = 1,
        };
        enum class animation_loop_mode_t : u8
        {
            one_shot = 0,
            continuous = 1,
        };
        enum class animation_state_t : u8
        {
            stop = 0,
            pause = 1,
            play = 2,
            continue_ = 3,
        };

        constexpr entity_control() = default;
        constexpr entity_control(const entity_control&) = default;
        constexpr entity_control(entity_control&&) noexcept = default;
        constexpr ~entity_control() = default;
        constexpr auto operator =(const entity_control& other) -> entity_control&
        {
            entity_id = other.entity_id;
            entity_state = other.entity_state;
            attach_state = other.attach_state;
            collision_detection_enable = other.collision_detection_enable;
            inherit_alpha = other.inherit_alpha;
            ground_ocean_clamp = other.ground_ocean_clamp;
            animation_direction = other.animation_direction;
            animation_loop_mode = other.animation_loop_mode;
            animation_state = other.animation_state;
            linear_extrapolation_interpolation_enable = other.linear_extrapolation_interpolation_enable;
            alpha = other.alpha;
            entity_type = other.entity_type;
            parent_id = other.parent_id;
            roll = other.roll;
            pitch = other.pitch;
            yaw = other.yaw;
            x_offset = other.x_offset;
            y_offset = other.y_offset;
            z_offset = other.z_offset;

            return *this;
        };

        static auto serialize(const entity_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, entity_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 2> packet_id;
        constant<u8, 48> packet_size;
        u16 entity_id = 0;
        active_t entity_state : 2 = active_t::inactive;
        attach_t attach_state : 1 = attach_t::detach;
        enable_t collision_detection_enable : 1 = enable_t::disabled;
        inherit_t inherit_alpha : 1 = inherit_t::not_inherited;
        ground_ocean_clamp_t ground_ocean_clamp : 2 = ground_ocean_clamp_t::no_clamp;
    private:
        u8 reserved_0 : 1 = 0;
    public:
        animation_direction_t animation_direction : 1 = animation_direction_t::forward;
        animation_loop_mode_t animation_loop_mode : 1 = animation_loop_mode_t::one_shot;
        animation_state_t animation_state : 2 = animation_state_t::stop;
        enable_t linear_extrapolation_interpolation_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_1 : 3 = 0;
    public:
        u8 alpha = 0;
    private:
        constant<u8, 0> reserved_2;
    public:
        u16 entity_type = 0;
        u16 parent_id = 0;
        bounded<f32, -180.f, 180.f> roll = 0.f;
        bounded<f32, -90.f, 90.f> pitch = 0.f;
        bounded<f32, 0.f, 360.f> yaw = 0.f;
        union
        {
            bounded<f64, -90.0, 90.0> latitude = 0.0;
            f64 x_offset;
        };
        union
        {
            bounded<f64, -180.0, 180.0> longitude = 0.0;
            f64 y_offset;
        };
        union
        {
            f64 altitude = 0.0;
            f64 z_offset;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::entity_control::ground_ocean_clamp_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::entity_control::ground_ocean_clamp_t;
    case no_clamp:
        return o << "no_clamp";
    case non_conformal:
        return o << "non-conformal";
    case conformal:
        return o << "conformal";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::entity_control::animation_direction_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::entity_control::animation_direction_t;
    case forward:
        return o << "forward";
    case backward:
        return o << "backward";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::entity_control::animation_loop_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::entity_control::animation_loop_mode_t;
    case one_shot:
        return o << "one-shot";
    case continuous:
        return o << "continuous";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::entity_control::animation_state_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::entity_control::animation_state_t;
    case stop:
        return o << "stop";
    case pause:
        return o << "pause";
    case play:
        return o << "play";
    case continue_:
        return o << "continue";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::entity_control& value) -> std::ostream&
{
    o << "entity_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tbitfield 1: (" << int(
                          (cigi::u8)value.ground_ocean_clamp << 5 
                        | (cigi::u8)value.inherit_alpha << 4
                        | (cigi::u8)value.collision_detection_enable << 3
                        | (cigi::u8)value.attach_state << 2
                        | (cigi::u8)value.entity_state) << ')';
    o << "\n\t\tentity_state: " << value.entity_state;
    o << "\n\t\tattach_state: " << value.attach_state;
    o << "\n\t\tcollision_detection_enable: " << value.collision_detection_enable;
    o << "\n\t\tinherit_alpha: " << value.inherit_alpha;
    o << "\n\t\tground_ocean_clamp: " << value.ground_ocean_clamp;
    o << "\n\tbitfield 2: (" << int(
                          (cigi::u8)value.linear_extrapolation_interpolation_enable << 4 
                        | (cigi::u8)value.animation_state << 2
                        | (cigi::u8)value.animation_loop_mode << 1
                        | (cigi::u8)value.animation_direction) << ')';
    o << "\n\t\tanimation_direction: " << value.animation_direction;
    o << "\n\t\tanimation_loop_mode: " << value.animation_loop_mode;
    o << "\n\t\tanimation_state: " << value.animation_state;
    o << "\n\t\tlinear_extrapolation_interpolation_enable: " << value.linear_extrapolation_interpolation_enable;
    o << "\n\talpha: " << (int)value.alpha;
    o << "\n\tentity_type: " << value.entity_type;
    o << "\n\tparent_id: " << value.parent_id;
    o << "\n\troll: " << value.roll;
    o << "\n\tpitch: " << value.pitch;
    o << "\n\tyaw: " << value.yaw;
    o << "\n\tx_offset: " << value.x_offset;
    o << "\n\ty_offset: " << value.y_offset;
    o << "\n\tz_offset: " << value.z_offset;

    return o << "\n}";
};