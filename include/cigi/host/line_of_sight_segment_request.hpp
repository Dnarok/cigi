#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.25
    struct line_of_sight_segment_request
    {
        constexpr line_of_sight_segment_request() = default;
        constexpr line_of_sight_segment_request(const line_of_sight_segment_request&) = default;
        constexpr line_of_sight_segment_request(line_of_sight_segment_request&&) noexcept = default;
        constexpr ~line_of_sight_segment_request() = default;
        constexpr auto operator =(const line_of_sight_segment_request& other) -> line_of_sight_segment_request&
        {
            los_id = other.los_id;
            request_type = other.request_type;
            source_point_coordinate_system = other.source_point_coordinate_system;
            destination_point_coordinate_system = other.destination_point_coordinate_system;
            response_coordinate_system = other.response_coordinate_system;
            destination_entity_id_valid = other.destination_entity_id_valid;
            alpha_threshold = other.alpha_threshold;
            source_entity_id = other.source_entity_id;
            source.latitude = other.source.latitude;
            source.longitude = other.source.longitude;
            source.altitude = other.source.altitude;
            destination.latitude = other.destination.latitude;
            destination.longitude = other.destination.longitude;
            destination.altitude = other.destination.altitude;
            material_mask = other.material_mask;
            update_period = other.update_period;
            destination_entity_id = other.destination_entity_id;

            return *this;
        };

        static auto serialize(const line_of_sight_segment_request& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, line_of_sight_segment_request& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 25> packet_id;
        constant<u8, 64> packet_size;
        u16 los_id = 0;
        request_type_t request_type : 1 = request_type_t::basic;
        coordinate_system_t source_point_coordinate_system : 1 = coordinate_system_t::geodetic;
        coordinate_system_t destination_point_coordinate_system : 1 = coordinate_system_t::geodetic;
        coordinate_system_t response_coordinate_system : 1 = coordinate_system_t::geodetic;
        valid_t destination_entity_id_valid : 1 = valid_t::invalid;
    private:
        u8 reserved_0 : 3 = 0;
    public:
        u8 alpha_threshold = 0;
        u16 source_entity_id = 0;
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
        } destination;
        u32 material_mask = 0;
        u8 update_period = 0;
    private:
        constant<u8, 0> reserved_1;
    public:
        u16 destination_entity_id = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::line_of_sight_segment_request& value) -> std::ostream&
{
    o << "line_of_sight_segment_request {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tlos_id: " << value.los_id;
    o << "\n\trequest_type: " << value.request_type;
    o << "\n\tsource_point_coordinate_system: " << value.source_point_coordinate_system;
    o << "\n\tdestination_point_coordinate_system: " << value.destination_point_coordinate_system;
    o << "\n\tresponse_coordinate_system: " << value.response_coordinate_system;
    o << "\n\tdestination_entity_id_valid: " << value.destination_entity_id_valid;
    o << "\n\talpha_threshold: " << (int)value.alpha_threshold;
    o << "\n\tsource_entity_id: " << value.source_entity_id;
    o << "\n\tsource latitude/x_offset: " << value.source.latitude;
    o << "\n\tsource longitude/y_offset: " << value.source.longitude;
    o << "\n\tsource altitude/z_offset: " << value.source.altitude;
    o << "\n\tdestination latitude/x_offset: " << value.destination.latitude;
    o << "\n\tdestination longitude/y_offset: " << value.destination.longitude;
    o << "\n\tdestination altitude/z_offset: " << value.destination.altitude;
    o << "\n\tmaterial_mask: " << value.material_mask;
    o << "\n\tupdate_period: " << (int)value.update_period;
    o << "\n\tdestination_entity_id: " << value.destination_entity_id;

    return o << "\n}";
};