#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.20
    struct alignas(std::uint64_t) trajectory_definition
    {
        constexpr trajectory_definition() = default;
        constexpr trajectory_definition(const trajectory_definition&) = default;
        constexpr trajectory_definition(trajectory_definition&&) noexcept = default;
        constexpr ~trajectory_definition() = default;
        constexpr auto operator =(const trajectory_definition& other) -> trajectory_definition&
        {
            entity_id = other.entity_id;
            acceleration_x = other.acceleration_x;
            acceleration_y = other.acceleration_y;
            acceleration_z = other.acceleration_z;
            retardation_rate = other.retardation_rate;
            terminal_velocity = other.terminal_velocity;

            return *this;
        };

        static auto serialize(const trajectory_definition& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, trajectory_definition& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 20> packet_id;
        constant<u8, 24> packet_size;
        u16 entity_id = 0;
        f32 acceleration_x = 0.f;
        f32 acceleration_y = 0.f;
        f32 acceleration_z = 0.f;
        f32 retardation_rate = 0.f;
        f32 terminal_velocity = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::trajectory_definition& value) -> std::ostream&
{
    o << "trajectory_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tacceleration_x: " << value.acceleration_x;
    o << "\n\tacceleration_y: " << value.acceleration_y;
    o << "\n\tacceleration_z: " << value.acceleration_z;
    o << "\n\tretardation_rate: " << value.retardation_rate;
    o << "\n\tterminal_velocity: " << value.terminal_velocity;

    return o << "\n}";
};