#pragma once

#include "general.hpp"
#include "sensor_response.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.7
    struct sensor_extended_response
    {
        using sensor_status_t = sensor_response::sensor_status_t;

        constexpr sensor_extended_response() = default;
        constexpr sensor_extended_response(const sensor_extended_response&) = default;
        constexpr sensor_extended_response(sensor_extended_response&&) noexcept = default;
        constexpr ~sensor_extended_response() = default;
        constexpr auto operator =(const sensor_extended_response& other) -> sensor_extended_response&
        {
            view_id = other.view_id;
            sensor_id = other.sensor_id;
            sensor_status = other.sensor_status;
            entity_id_valid = other.entity_id_valid;
            entity_id = other.entity_id;
            gate_x_size = other.gate_x_size;
            gate_y_size = other.gate_y_size;
            gate_x_offset = other.gate_x_offset;
            gate_y_offset = other.gate_y_offset;
            host_frame_number = other.host_frame_number;
            track_point_latitude = other.track_point_latitude;
            track_point_longitude = other.track_point_longitude;
            track_point_altitude = other.track_point_altitude;

            return *this;
        };

        static auto serialize(const sensor_extended_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, sensor_extended_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 107> packet_id;
        constant<u8, 48> packet_size;
        u16 view_id = 0;
        u8 sensor_id = 0;
        sensor_status_t sensor_status : 2 = sensor_status_t::searching_for_target;
        valid_t entity_id_valid : 1 = valid_t::invalid;
    private:
        u8 reserved_0 : 5 = 0;
    public:
        u16 entity_id = 0;
        u16 gate_x_size = 0;
        u16 gate_y_size = 0;
        f32 gate_x_offset = 0;
        f32 gate_y_offset = 0;
        u32 host_frame_number = 0;
        bounded<f64, -90.0, 90.0> track_point_latitude = 0;
        bounded<f64, -180.0, 180.0> track_point_longitude = 0;
        f64 track_point_altitude = 0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::sensor_extended_response& value) -> ostream&
{
    o << "sensor_extended_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tview_id: " << value.view_id;
    o << "\n\tsensor_id: " << (int)value.sensor_id;
    o << "\n\tsensor_status: " << value.sensor_status;
    o << "\n\tentity_id_valid: " << value.entity_id_valid;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tgate_x_size: " << value.gate_x_size;
    o << "\n\tgate_y_size: " << value.gate_y_size;
    o << "\n\tgate_x_offset: " << value.gate_x_offset;
    o << "\n\tgate_y_offset: " << value.gate_y_offset;
    o << "\n\thost_frame_number: " << value.host_frame_number;
    o << "\n\ttrack_point_latitude: " << value.track_point_latitude;
    o << "\n\ttrack_point_longitude: " << value.track_point_longitude;
    o << "\n\ttrack_point_altitude: " << value.track_point_altitude;

    return o << "\n}";
};

/*
view_id
sensor_id
sensor_status
entity_id_valid
entity_id
gate_x_size
gate_y_size
gate_x_offset
gate_y_offset
host_frame_number
track_point_latitude
track_point_longitude
track_point_altitude
*/