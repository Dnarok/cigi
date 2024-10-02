#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.9
    struct alignas(std::uint64_t) weather_conditions_response
    {
        constexpr weather_conditions_response() = default;
        constexpr weather_conditions_response(const weather_conditions_response&) = default;
        constexpr weather_conditions_response(weather_conditions_response&&) noexcept = default;
        constexpr ~weather_conditions_response() = default;
        constexpr auto operator =(const weather_conditions_response& other) -> weather_conditions_response&
        {
            request_id = other.request_id;
            humidity = other.humidity;
            air_temperature = other.air_temperature;
            visibility_range = other.visibility_range;
            horizontal_wind_speed = other.horizontal_wind_speed;
            vertical_wind_speed = other.vertical_wind_speed;
            wind_direction = other.wind_direction;
            barometric_pressure = other.barometric_pressure;

            return *this;
        };

        static auto serialize(const weather_conditions_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, weather_conditions_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 109> packet_id;
        constant<u8, 32> packet_size;
        u8 request_id = 0;
        bounded<u8, 0, 100> humidity = 0;
        f32 air_temperature = 0;
        bounded<f32, 0.f> visibility_range = 0.f;
        bounded<f32, 0.f> horizontal_wind_speed = 0.f;
        f32 vertical_wind_speed = 0.f;
        bounded<f32, 0.f, 360.f> wind_direction = 0.f;
        bounded<f32, 0.f> barometric_pressure = 0.f;
    private:
        constant<u32, 0> reserved_0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::weather_conditions_response& value) -> ostream&
{
    o << "weather_conditions_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\trequest_id: " << (int)value.request_id;
    o << "\n\thumidity: " << (int)value.humidity;
    o << "\n\tair_temperature: " << value.air_temperature;
    o << "\n\tvisibility_range: " << value.visibility_range;
    o << "\n\thorizontal_wind_speed: " << value.horizontal_wind_speed;
    o << "\n\tvertical_wind_speed: " << value.vertical_wind_speed;
    o << "\n\twind_direction: " << value.wind_direction;
    o << "\n\tbarometric_pressure: " << value.barometric_pressure;

    return o << "\n}";
};