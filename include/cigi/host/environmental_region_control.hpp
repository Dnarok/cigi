#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.11
    struct environmental_region_control
    {
        constexpr environmental_region_control() = default;
        constexpr environmental_region_control(const environmental_region_control&) = default;
        constexpr environmental_region_control(environmental_region_control&&) noexcept = default;
        constexpr ~environmental_region_control() = default;
        constexpr auto operator =(const environmental_region_control& other) -> environmental_region_control&
        {
            region_id = other.region_id;
            region_state = other.region_state;
            merge_weather_properties = other.merge_weather_properties;
            merge_aerosol_concentrations = other.merge_aerosol_concentrations;
            merge_maritime_surface_conditions = other.merge_maritime_surface_conditions;
            merge_terrestrial_surface_conditions = other.merge_terrestrial_surface_conditions;
            latitude = other.latitude;
            longitude = other.longitude;
            size_x = other.size_x;
            size_y = other.size_y;
            corner_radius = other.corner_radius;
            transition_perimeter = other.transition_perimeter;

            return *this;
        };

        static auto serialize(const environmental_region_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, environmental_region_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 11> packet_id;
        constant<u8, 48> packet_size;
        u16 region_id = 0;
        active_t region_state : 2 = active_t::inactive;
        merge_t merge_weather_properties : 1 = merge_t::use_last;
        merge_t merge_aerosol_concentrations : 1 = merge_t::use_last;
        merge_t merge_maritime_surface_conditions : 1 = merge_t::use_last;
        merge_t merge_terrestrial_surface_conditions : 1 = merge_t::use_last;
    private:
        u8 reserved_0 : 2 = 0;
        constant<u8, 0> reserved_1;
        constant<u16, 0> reserved_2;
    public:
        bounded<f64, -90.0, 90.0> latitude = 0.0;
        bounded<f64, -180.0, 180.0> longitude = 0.0;
        bounded<f32, 0.f> size_x = 0.f;
        bounded<f32, 0.f> size_y = 0.f;
        bounded<f32, 0.f> corner_radius = 0.f;
        bounded<f32, -180.f, 180.f> rotation = 0.f;
        bounded<f32, 0.f> transition_perimeter = 0.f;
    private:
        constant<u32, 0> reserved_3;
    };
};

inline auto operator <<(std::ostream& o, const cigi::environmental_region_control& value) -> std::ostream&
{
    o << "environmental_region_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tregion_id: " << value.region_id;
    o << "\n\tregion_state: " << value.region_state;
    o << "\n\tmerge_weather_properties: " << value.merge_weather_properties;
    o << "\n\tmerge_aerosol_concentrations: " << value.merge_aerosol_concentrations;
    o << "\n\tmerge_maritime_surface_conditions: " << value.merge_maritime_surface_conditions;
    o << "\n\tmerge_terrestrial_surface_conditions: " << value.merge_terrestrial_surface_conditions;
    o << "\n\tlatitude: " << value.latitude;
    o << "\n\tlongitude: " << value.longitude;
    o << "\n\tsize_x: " << value.size_x;
    o << "\n\tsize_y: " << value.size_y;
    o << "\n\tcorner_radius: " << value.corner_radius;
    o << "\n\trotation: " << value.rotation;
    o << "\n\ttransition_perimeter: " << value.transition_perimeter;

    return o << "\n}";
};