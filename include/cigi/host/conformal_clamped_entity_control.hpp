#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.3
    struct conformal_clamped_entity_control
    {
        constexpr conformal_clamped_entity_control() = default;
        constexpr conformal_clamped_entity_control(const conformal_clamped_entity_control&) = default;
        constexpr conformal_clamped_entity_control(conformal_clamped_entity_control&&) noexcept = default;
        constexpr ~conformal_clamped_entity_control() = default;
        constexpr auto operator =(const conformal_clamped_entity_control& other) -> conformal_clamped_entity_control&
        {
            entity_id = other.entity_id;
            yaw = other.yaw;
            latitude = other.latitude;
            longitude = other.longitude;

            return *this;
        };

        static auto serialize(const conformal_clamped_entity_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, conformal_clamped_entity_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 3> packet_id;
        constant<u8, 24> packet_size;
        u16 entity_id = 0;
        bounded<f32, 0.f, 360.f> yaw = 0.f;
        bounded<f64, -90.0, 90.0> latitude = 0.0;
        bounded<f64, -180.0, 180.0> longitude = 0.0;
    };
}

inline auto operator <<(std::ostream& o, const cigi::conformal_clamped_entity_control& value) -> std::ostream&
{
    o << "conformal_clamped_entity_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tyaw: " << value.yaw;
    o << "\n\tlatitude: " << value.latitude;
    o << "\n\tlongitude: " << value.longitude;

    return o << "\n}";
}