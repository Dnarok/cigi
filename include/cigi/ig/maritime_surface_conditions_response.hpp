#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.11
    struct alignas(std::uint64_t) maritime_surface_conditions_response
    {
        constexpr maritime_surface_conditions_response() = default;
        constexpr maritime_surface_conditions_response(const maritime_surface_conditions_response&) = default;
        constexpr maritime_surface_conditions_response(maritime_surface_conditions_response&&) noexcept = default;
        constexpr ~maritime_surface_conditions_response() = default;
        constexpr auto operator =(const maritime_surface_conditions_response& other) -> maritime_surface_conditions_response&
        {
            request_id = other.request_id;
            sea_surface_height = other.sea_surface_height;
            surface_water_temperature = other.surface_water_temperature;
            surface_clarity = other.surface_clarity;

            return *this;
        };

        static auto serialize(const maritime_surface_conditions_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, maritime_surface_conditions_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 111> packet_id;
        constant<u8, 16> packet_size;
        u8 request_id = 0;
    private:
        constant<u8, 0> reserved_0;
    public:
        f32 sea_surface_height = 0.f;
        f32 surface_water_temperature = 0.f;
        bounded<f32, 0.f, 100.f> surface_clarity = 0.f;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::maritime_surface_conditions_response& value) -> ostream&
{
    o << "maritime_surface_conditions_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\trequest_id: " << (int)value.request_id;
    o << "\n\tsea_surface_height: " << value.sea_surface_height;
    o << "\n\tsurface_water_temperature: " << value.surface_water_temperature;
    o << "\n\tsurface_clarity: " << value.surface_clarity;

    return o << "\n}";
};

/*
request_id
sea_surface_height
surface_water_temperature
surface_clarity
*/