#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.26
    struct line_of_sight_vector_request
    {
        constexpr line_of_sight_vector_request() = default;
        constexpr line_of_sight_vector_request(const line_of_sight_vector_request&) = default;
        constexpr line_of_sight_vector_request(line_of_sight_vector_request&&) noexcept = default;
        constexpr ~line_of_sight_vector_request() = default;
        constexpr auto operator =(const line_of_sight_vector_request& other) -> line_of_sight_vector_request&
        {
            los_id = other.los_id;
            request_type = other.request_type;
            source_point_coordinate_system = other.source_point_coordinate_system;
            response_coordinate_system = other.response_coordinate_system;
            alpha_threshold = other.alpha_threshold;
            entity_id = other.entity_id;
            azimuth = other.azimuth;
            elevation = other.elevation;
            minimum_range = other.minimum_range;
            maximum_range = other.maximum_range;
            source.latitude = other.source.latitude;
            source.longitude = other.source.longitude;
            source.altitude = other.source.altitude;
            material_mask = other.material_mask;
            update_period = other.update_period;

            return *this;
        };

        static auto serialize(const line_of_sight_vector_request& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, line_of_sight_vector_request& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 26> packet_id;
        constant<u8, 56> packet_size;
        u16 los_id = 0;
        request_type_t request_type : 1 = request_type_t::basic;
        coordinate_system_t source_point_coordinate_system : 1 = coordinate_system_t::geodetic;
        coordinate_system_t response_coordinate_system : 1 = coordinate_system_t::geodetic;
    private:
        u8 reserved_0 : 5 = 0;
    public:
        u8 alpha_threshold = 0;
        u16 entity_id = 0;
        bounded<f32, -180.f, 180.f> azimuth = 0.f;
        bounded<f32, -90.f, 90.f> elevation = 0.f;
        bounded<f32, 0.f> minimum_range = 0.f;
        bounded<f32, 0.f> maximum_range = 0.f;
        struct
        {
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
        } source;
        u32 material_mask = 0;
        u8 update_period = 0;
    private:
        constant<u8, 0> reserved_1;
        constant<u16, 0> reserved_2;
    };
};

inline auto operator <<(std::ostream& o, const cigi::line_of_sight_vector_request& value) -> std::ostream&
{
    o << "line_of_sight_vector_request {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tlos_id: " << value.los_id;
    o << "\n\trequest_type: " << value.request_type;
    o << "\n\tsource_point_coordinate_system: " << value.source_point_coordinate_system;
    o << "\n\tresponse_coordinate_system: " << value.response_coordinate_system;
    o << "\n\talpha_threshold: " << (int)value.alpha_threshold;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tazimuth: " << value.azimuth;
    o << "\n\televation: " << value.elevation;
    o << "\n\tminimum_range: " << value.minimum_range;
    o << "\n\tmaximum_range: " << value.maximum_range;
    o << "\n\tsource latitude/x_offset: " << value.source.latitude;
    o << "\n\tsource longitude/y_offset: " << value.source.longitude;
    o << "\n\tsource altitude/z_offset: " << value.source.altitude;
    o << "\n\tmaterial_mask: " << value.material_mask;
    o << "\n\tupdate_period: " << (int)value.update_period;

    return o << "\n}";
};