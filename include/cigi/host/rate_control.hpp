#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.8
    struct alignas(std::uint64_t) rate_control
    {
        enum class coordinate_system_t : u8
        {
            world = 0,
            parent = world,
            local = 1,
        };

        constexpr rate_control() = default;
        constexpr rate_control(const rate_control&) = default;
        constexpr rate_control(rate_control&&) noexcept = default;
        constexpr ~rate_control() = default;
        constexpr auto operator =(const rate_control& other) -> rate_control&
        {
            entity_id = other.entity_id;
            articulated_part_id = other.articulated_part_id;
            apply_to_articulated_part = other.apply_to_articulated_part;
            coordinate_system = other.coordinate_system;
            x_linear_rate = other.x_linear_rate;
            y_linear_rate = other.y_linear_rate;
            z_linear_rate = other.z_linear_rate;
            roll_angular_rate = other.roll_angular_rate;
            pitch_angular_rate = other.pitch_angular_rate;
            yaw_angular_rate = other.yaw_angular_rate;

            return *this;
        };

        static auto serialize(const rate_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, rate_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 8> packet_id;
        constant<u8, 32> packet_size;
        u16 entity_id = 0;
        u8 articulated_part_id = 0;
        bool apply_to_articulated_part : 1 = false;
        coordinate_system_t coordinate_system : 1 = coordinate_system_t::world;
    private:
        u8 reserved_0 : 6 = 0;
        u16 reserved_1 = 0;
    public:
        f32 x_linear_rate = 0.f;
        f32 y_linear_rate = 0.f;
        f32 z_linear_rate = 0.f;
        f32 roll_angular_rate = 0.f;
        f32 pitch_angular_rate = 0.f;
        f32 yaw_angular_rate = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::rate_control::coordinate_system_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::rate_control::coordinate_system_t;
    case world:
        return o << "world/parent";
    case local:
        return o << "local";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::rate_control& value) -> std::ostream&
{
    o << "rate_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tarticulated_part_id: " << (int)value.articulated_part_id;
    o << "\n\tapply_to_articulated_part: " << value.apply_to_articulated_part;
    o << "\n\tcoordinate_system: " << value.coordinate_system;
    o << "\n\tx_linear_rate: " << value.x_linear_rate;
    o << "\n\ty_linear_rate: " << value.y_linear_rate;
    o << "\n\tz_linear_rate: " << value.z_linear_rate;
    o << "\n\troll_angular_rate: " << value.roll_angular_rate;
    o << "\n\tpitch_angular_rate: " << value.pitch_angular_rate;
    o << "\n\tyaw_angular_rate: " << value.yaw_angular_rate;

    return o << "\n}";
};