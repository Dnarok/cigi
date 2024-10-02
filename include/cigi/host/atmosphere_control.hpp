#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.10
    struct alignas(std::uint64_t) atmosphere_control
    {
        constexpr atmosphere_control() = default;
        constexpr atmosphere_control(const atmosphere_control&) = default;
        constexpr atmosphere_control(atmosphere_control&&) noexcept = default;
        constexpr ~atmosphere_control() = default;
        constexpr auto operator =(const atmosphere_control& other) -> atmosphere_control&
        {
            atmospheric_model_enable = other.atmospheric_model_enable;
            global_humidity = other.global_humidity;
            global_air_temperature = other.global_air_temperature;
            global_visibility_range = other.global_visibility_range;
            global_horizontal_wind_speed = other.global_horizontal_wind_speed;
            global_vertical_wind_speed = other.global_vertical_wind_speed;
            global_wind_direction = other.global_wind_direction;
            global_barometric_pressure = other.global_barometric_pressure;

            return *this;
        };

        static auto serialize(const atmosphere_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, atmosphere_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 10> packet_id;
        constant<u8, 32> packet_size;
        enable_t atmospheric_model_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_0 : 7 = 0;
    public:
        bounded<u8, 0, 100> global_humidity = 0;
        f32 global_air_temperature = 0.f;
        bounded<f32, 0.f> global_visibility_range = 0.f;
        bounded<f32, 0.f> global_horizontal_wind_speed = 0.f;
        f32 global_vertical_wind_speed = 0.f;
        bounded<f32, 0.f, 360.f> global_wind_direction = 0.f;
        bounded<f32, 0.f> global_barometric_pressure = 0.f;
    private:
        constant<u32, 0> reserved_1;
    };
};

inline auto operator <<(std::ostream& o, const cigi::atmosphere_control& value) -> std::ostream&
{
    o << "atmosphere_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tatmospheric_model_enable: " << value.atmospheric_model_enable;
    o << "\n\tglobal_humidity: " << (int)value.global_humidity.value;
    o << "\n\tglobal_air_temperature: " << value.global_air_temperature;
    o << "\n\tglobal_visibility_range: " << value.global_visibility_range;
    o << "\n\tglobal_horizontal_wind_speed: " << value.global_horizontal_wind_speed;
    o << "\n\tglobal_vertical_wind_speed: " << value.global_vertical_wind_speed;
    o << "\n\tglobal_wind_direction: " << value.global_wind_direction;
    o << "\n\tglobal_barometric_pressure: " << value.global_barometric_pressure;

    return o << "\n}";
};