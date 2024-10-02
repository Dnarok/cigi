#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.12
    struct alignas(std::uint64_t) weather_control
    {
        enum class layer_t : u8
        {
            ground_fog = 0,
            cloud_layer_1 = 1,
            cloud_layer_2 = 2,
            cloud_layer_3 = 3,
            rain = 4,
            snow = 5,
            sleet = 6,
            hail = 7,
            sand = 8,
            dust = 9,
        };
        enum class cloud_type_t : u8
        {
            none = 0,
            altocumulus = 1,
            altostratus = 2,
            cirrocumulus = 3,
            cirrostratus = 4,
            cirrus = 5,
            cumulonimbus = 6,
            cumulus = 7,
            nimbostratus = 8,
            stratocumulus = 9,
            stratus = 10,
            other_1 = 11,
            other_2 = 12,
            other_3 = 13,
            other_4 = 14,
            other_5 = 15,
        };

        constexpr weather_control() = default;
        constexpr weather_control(const weather_control&) = default;
        constexpr weather_control(weather_control&&) noexcept = default;
        constexpr ~weather_control() = default;
        constexpr auto operator =(const weather_control& other) -> weather_control&
        {
            entity_id = other.entity_id;
            layer_id = other.layer_id;
            humidity = other.humidity;
            weather_enable = other.weather_enable;
            scud_enable = other.scud_enable;
            random_winds_enable = other.random_winds_enable;
            random_lightning_enable = other.random_lightning_enable;
            cloud_type = other.cloud_type;
            scope = other.scope;
            severity = other.severity;
            air_temperature = other.air_temperature;
            visibility_range = other.visibility_range;
            scud_frequency = other.scud_frequency;
            coverage = other.coverage;
            base_elevation = other.base_elevation;
            thickness = other.thickness;
            transition_band = other.transition_band;
            horizontal_wind_speed = other.horizontal_wind_speed;
            vertical_wind_speed = other.vertical_wind_speed;
            wind_direction = other.wind_direction;
            barometric_pressure = other.barometric_pressure;
            aerosol_concentration = other.aerosol_concentration;

            return *this;
        };

        static auto serialize(const weather_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, weather_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 12> packet_id;
        constant<u8, 56> packet_size;
        union
        {
            u16 entity_id = 0;
            u16 region_id;
        };
        layer_t layer_id = layer_t::ground_fog;
        bounded<u8, 0, 100> humidity = 0;
        enable_t weather_enable : 1 = enable_t::disabled;
        enable_t scud_enable : 1 = enable_t::disabled;
        enable_t random_winds_enable : 1 = enable_t::disabled;
        enable_t random_lightning_enable : 1 = enable_t::disabled;
        cloud_type_t cloud_type : 4 = cloud_type_t::none;
        scope_t scope : 2 = scope_t::global;
        u8 severity : 3 = 0;
    private:
        u8 reserved_0 : 3 = 0;
    public:
        f32 air_temperature = 0.f;
        f32 visibility_range = 0.f;
        bounded<f32, 0.f, 100.f> scud_frequency = 0.f;
        bounded<f32, 0.f, 100.f> coverage = 0.f;
        f32 base_elevation = 0.f;
        f32 thickness = 0.f;
        f32 transition_band = 0.f;
        bounded<f32, 0.f> horizontal_wind_speed = 0.f;
        f32 vertical_wind_speed = 0.f;
        bounded<f32, 0.f, 360.f> wind_direction = 0.f;
        bounded<f32, 0.f> barometric_pressure = 0.f;
        bounded<f32, 0.f> aerosol_concentration = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::weather_control::layer_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::weather_control::layer_t;
    case ground_fog:
        return o << "ground fog";
    case cloud_layer_1:
        return o << "cloud layer 1";
    case cloud_layer_2:
        return o << "cloud layer 2";
    case cloud_layer_3:
        return o << "cloud layer 3";
    case rain:
        return o << "rain";
    case snow:
        return o << "snow";
    case sleet:
        return o << "sleet";
    case hail:
        return o << "hail";
    case sand:
        return o << "sand";
    case dust:
        return o << "dust";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::weather_control::cloud_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::weather_control::cloud_type_t;
    case none:
        return o << "none";
    case altocumulus:
        return o << "altocumulus";
    case altostratus:
        return o << "altostratus";
    case cirrocumulus:
        return o << "cirrocumulus";
    case cirrostratus:
        return o << "cirrostratus";
    case cirrus:
        return o << "cirrus";
    case cumulonimbus:
        return o << "cumulonimbus";
    case cumulus:
        return o << "cumulus";
    case nimbostratus:
        return o << "nimbostratus";
    case stratocumulus:
        return o << "stratocumulus";
    case stratus:
        return o << "stratus";
    case other_1:
    case other_2:
    case other_3:
    case other_4:
    case other_5:
        return o << "other";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::weather_control& value) -> std::ostream&
{
    o << "weather_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tlayer_id: " << value.layer_id;
    o << "\n\thumidity: " << (int)value.humidity.value;
    o << "\n\tweather_enable: " << value.weather_enable;
    o << "\n\tscud_enable: " << value.scud_enable;
    o << "\n\trandom_winds_enable: " << value.random_winds_enable;
    o << "\n\trandom_lightning_enable: " << value.random_lightning_enable;
    o << "\n\tcloud_type: " << value.cloud_type;
    o << "\n\tscope: " << value.scope;
    o << "\n\tseverity: " << (int)value.severity;
    o << "\n\tair_temperature: " << value.air_temperature;
    o << "\n\tvisibility_range: " << value.visibility_range;
    o << "\n\tscud_frequency: " << value.scud_frequency;
    o << "\n\tcoverage: " << value.coverage;
    o << "\n\tbase_elevation: " << value.base_elevation;
    o << "\n\tthickness: " << value.thickness;
    o << "\n\ttransition_band: " << value.transition_band;
    o << "\n\thorizontal_wind_speed: " << value.horizontal_wind_speed;
    o << "\n\tvertical_wind_speed: " << value.vertical_wind_speed;
    o << "\n\twind_direction: " << value.wind_direction;
    o << "\n\tbarometric_pressure: " << value.barometric_pressure;
    o << "\n\taerosol_concentration: " << value.aerosol_concentration;

    return o << "\n}";
};