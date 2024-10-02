#pragma once

#include "general.hpp"
#include <bitset>

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.28
    struct environmental_conditions_request
    {
        // flag type
        enum class request_type_t : u8
        {
            none = 0,
            maritime_surface_conditions = 1 << 0,
            terrestrial_surface_conditions = 1 << 1,
            weather_conditions = 1 << 2,
            aerosol_concentrations = 1 << 3,
        };

        constexpr environmental_conditions_request() = default;
        constexpr environmental_conditions_request(const environmental_conditions_request&) = default;
        constexpr environmental_conditions_request(environmental_conditions_request&&) noexcept = default;
        constexpr ~environmental_conditions_request() = default;
        constexpr auto operator =(const environmental_conditions_request& other) -> environmental_conditions_request&
        {
            request_type = other.request_type;
            request_id = other.request_id;
            latitude = other.latitude;
            longitude = other.longitude;
            altitude = other.altitude;

            return *this;
        };

        static auto serialize(const environmental_conditions_request& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, environmental_conditions_request& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 28> packet_id;
        constant<u8, 32> packet_size;
        request_type_t request_type : 4 = request_type_t::none;
    private:
        u8 reserved_0 : 4 = 0;
    public:
        u8 request_id = 0;
    private:
        constant<u32, 0> reserved_1;
    public:
        bounded<f64, -90.0, 90.0> latitude = 0;
        bounded<f64, -180.0, 180.0> longitude = 0;
        f64 altitude = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::environmental_conditions_request::request_type_t& value) -> std::ostream&
{
    std::bitset<8> bits = cigi::u8(value);
    if (bits.none())
    {
        return o << "none";
    }

    bool do_comma = false;
    if (bits[0])
    {
        o << "maritime surface conditions";
        do_comma = true;
    }
    if (bits[1])
    {
        if (do_comma)
        {
            o << ", ";
        }
        o << "terrestrial surface conditions";
        do_comma = true;
    }
    if (bits[2])
    {
        if (do_comma)
        {
            o << ", ";
        }
        o << "weather conditions";
        do_comma = true;
    }
    if (bits[3])
    {
        if (do_comma)
        {
            o << ", ";
        }
        o << "aerosol concentrations";
        do_comma = true;
    }

    return o;
};

constexpr auto operator |(const cigi::environmental_conditions_request::request_type_t& left, const cigi::environmental_conditions_request::request_type_t& right) -> cigi::environmental_conditions_request::request_type_t
{
    return cigi::environmental_conditions_request::request_type_t(cigi::u8(left) | cigi::u8(right));
};

inline auto operator <<(std::ostream& o, const cigi::environmental_conditions_request& value) -> std::ostream&
{
    o << "environmental_conditions_request {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\trequest_type: " << value.request_type;
    o << "\n\trequest_id: " << (int)value.request_id;
    o << "\n\tlatitude: " << value.latitude;
    o << "\n\tlongitude: " << value.longitude;
    o << "\n\taltitude: " << value.altitude;

    return o << "\n}";
};