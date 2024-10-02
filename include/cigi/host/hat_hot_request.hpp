#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.24
    struct hat_hot_request
    {
        enum class request_type_t : u8
        {
            hat = 0,
            hot = 1,
            extended = 2,
        };

        constexpr hat_hot_request() = default;
        constexpr hat_hot_request(const hat_hot_request&) = default;
        constexpr hat_hot_request(hat_hot_request&&) noexcept = default;
        constexpr ~hat_hot_request() = default;
        constexpr auto operator =(const hat_hot_request& other) -> hat_hot_request&
        {
            hat_hod_id = other.hat_hod_id;
            request_type = other.request_type;
            coordinate_system = other.coordinate_system;
            update_period = other.update_period;
            entity_id = other.entity_id;
            latitude = other.latitude;
            longitude = other.longitude;
            altitude = other.altitude;

            return *this;
        };

        static auto serialize(const hat_hot_request& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, hat_hot_request& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 24> packet_id;
        constant<u8, 32> packet_size;
        u16 hat_hod_id = 0;
        request_type_t request_type : 2 = request_type_t::hat;
        coordinate_system_t coordinate_system : 1 = coordinate_system_t::geodetic;
    private:
        u8 reserved_0 : 5 = 0;
    public:
        u8 update_period = 0;
        u16 entity_id = 0;
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

inline auto operator <<(std::ostream& o, const cigi::hat_hot_request::request_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::hat_hot_request::request_type_t;
    case hat:
        return o << "HAT";
    case hot:
        return o << "HOT";
    case extended:
        return o << "extended";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::hat_hot_request& value) -> std::ostream&
{
    o << "hat_hot_request {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\that_hod_id: " << value.hat_hod_id;
    o << "\n\trequest_type: " << value.request_type;
    o << "\n\tcoordinate_system: " << value.coordinate_system;
    o << "\n\tupdate_period: " << (int)value.update_period;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tlatitude: " << value.latitude;
    o << "\n\tlongitude: " << value.longitude;
    o << "\n\taltitude: " << value.altitude;

    return o << "\n}";
};