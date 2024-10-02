#pragma once

#include "general.hpp"
#include "host/position_request.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.8
    struct alignas(std::uint64_t) position_response
    {
        using object_class_t = position_request::object_class_t;
        using coordinate_system_t = position_request::coordinate_system_t;

        constexpr position_response() = default;
        constexpr position_response(const position_response&) = default;
        constexpr position_response(position_response&&) noexcept = default;
        constexpr ~position_response() = default;
        constexpr auto operator =(const position_response& other) -> position_response&
        {
            object_id = other.object_id;
            articulated_part_id = other.articulated_part_id;
            object_class = other.object_class;
            coordinate_system = other.coordinate_system;
            latitude = other.latitude;
            longitude = other.longitude;
            altitude = other.altitude;
            roll = other.roll;
            pitch = other.pitch;
            yaw = other.yaw;

            return *this;
        };

        static auto serialize(const position_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, position_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 108> packet_id;
        constant<u8, 48> packet_size;
        u16 object_id = 0;
        u8 articulated_part_id = 0;
        object_class_t object_class : 3 = object_class_t::entity;
        coordinate_system_t coordinate_system : 2 = coordinate_system_t::geodetic;
    private:
        u8 reserved_0 : 3 = 0;
        constant<u16, 0> reserved_1;
    public:
        union
        {
            f64 x_offset = 0.0;
            bounded<f64, -90.0, 90.0> latitude;
        };
        union
        {
            f64 y_offset = 0.0;
            bounded<f64, -180.0, 180.0> longitude;
        };
        union
        {
            f64 z_offset = 0.0;
            f64 altitude;
        };
        bounded<f32, -180.f, 180.f> roll = 0.f;
        bounded<f32, -90.f, 90.f> pitch = 0.f;
        bounded<f32, 0.f, 360.f> yaw = 0.f;
    private:
        constant<u32, 0> reserved_2;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::position_response& value) -> ostream&
{
    o << "position_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tobject_id: " << value.object_id;
    o << "\n\tarticulated_part_id: " << (int)value.articulated_part_id;
    o << "\n\tobject_class: " << value.object_class;
    o << "\n\tcoordinate_system: " << value.coordinate_system;
    o << "\n\tlatitude/x_offset: " << value.latitude;
    o << "\n\tlongitude/y_offset: " << value.longitude;
    o << "\n\taltitude/z_offset: " << value.altitude;
    o << "\n\troll: " << value.roll;
    o << "\n\tpitch: " << value.pitch;
    o << "\n\tyaw: " << value.yaw;

    return o << "\n}";
};