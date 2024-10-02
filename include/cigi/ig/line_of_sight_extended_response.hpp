#pragma once

#include "general.hpp"
#include "line_of_sight_response.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.5
    struct line_of_sight_extended_response
    {
        using visible_t = line_of_sight_response::visible_t;

        constexpr line_of_sight_extended_response() = default;
        constexpr line_of_sight_extended_response(const line_of_sight_extended_response&) = default;
        constexpr line_of_sight_extended_response(line_of_sight_extended_response&&) noexcept = default;
        constexpr ~line_of_sight_extended_response() = default;
        constexpr auto operator =(const line_of_sight_extended_response& other) -> line_of_sight_extended_response&
        {
            los_id = other.los_id;
            valid = other.valid;
            entity_id_valid = other.entity_id_valid;
            range_valid = other.range_valid;
            visible = other.visible;
            host_frame_number_lsn = other.host_frame_number_lsn;
            response_count = other.response_count;
            entity_id = other.entity_id;
            range = other.range;
            latitude = other.latitude;
            longitude = other.longitude;
            altitude = other.altitude;
            red = other.red;
            green = other.green;
            blue = other.blue;
            alpha = other.alpha;
            material_code = other.material_code;
            normal_vector_azimuth = other.normal_vector_azimuth;
            normal_vector_elevation = other.normal_vector_elevation;

            return *this;
        };

        static auto serialize(const line_of_sight_extended_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, line_of_sight_extended_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 105> packet_id;
        constant<u8, 56> packet_size;
        u16 los_id = 0;
        valid_t valid : 1 = valid_t::invalid;
        valid_t entity_id_valid : 1 = valid_t::invalid;
        valid_t range_valid : 1 = valid_t::invalid;
        visible_t visible : 1 = visible_t::occluded;
        u8 host_frame_number_lsn : 4 = 0;
        u8 response_count = 0;
        u16 entity_id = 0;
        f64 range = 0;
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
        u8 red = 0;
        u8 green = 0;
        u8 blue = 0;
        u8 alpha = 0;
        u32 material_code = 0;
        bounded<f32, -180.f, 180.f> normal_vector_azimuth = 0;
        bounded<f32, -90.f, 90.f> normal_vector_elevation = 0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::line_of_sight_extended_response& value) -> ostream&
{
    o << "line_of_sight_extended_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tlos_id: " << value.los_id;
    o << "\n\tvalid: " << value.valid;
    o << "\n\tentity_id_valid: " << value.entity_id_valid;
    o << "\n\trange_valid: " << value.range_valid;
    o << "\n\tvisible: " << value.visible;
    o << "\n\thost_frame_number_lsn: " << (int)value.host_frame_number_lsn;
    o << "\n\tresponse_count: " << (int)value.response_count;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\trange: " << value.range;
    o << "\n\tlatitude/x_offset: " << value.latitude;
    o << "\n\tlongitude/y_offset: " << value.longitude;
    o << "\n\taltitude/z_offset: " << value.altitude;
    o << "\n\tred: " << (int)value.red;
    o << "\n\tgreen: " << (int)value.green;
    o << "\n\tblue: " << (int)value.blue;
    o << "\n\talpha: " << (int)value.alpha;
    o << "\n\tmaterial_code: " << value.material_code;
    o << "\n\tnormal_vector_azimuth: " << value.normal_vector_azimuth;
    o << "\n\tnormal_vector_elevation: " << value.normal_vector_elevation;

    return o << "\n}";
};