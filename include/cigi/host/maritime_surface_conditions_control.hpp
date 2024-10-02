#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.13
    struct alignas(std::uint64_t) maritime_surface_conditions_control
    {
        constexpr maritime_surface_conditions_control() = default;
        constexpr maritime_surface_conditions_control(const maritime_surface_conditions_control&) = default;
        constexpr maritime_surface_conditions_control(maritime_surface_conditions_control&&) noexcept = default;
        constexpr ~maritime_surface_conditions_control() = default;
        constexpr auto operator =(const maritime_surface_conditions_control& other) -> maritime_surface_conditions_control&
        {
            entity_id = other.entity_id;
            surface_conditions_enable = other.surface_conditions_enable;
            whitecap_enable = other.whitecap_enable;
            scope = other.scope;
            sea_surface_height = other.sea_surface_height;
            surface_water_temperature = other.surface_water_temperature;
            surface_clarity = other.surface_clarity;

            return *this;
        };

        static auto serialize(const maritime_surface_conditions_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, maritime_surface_conditions_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 13> packet_id;
        constant<u8, 24> packet_size;
        union
        {
            u16 entity_id = 0;
            u16 region_id;
        };
        enable_t surface_conditions_enable : 1 = enable_t::disabled;
        enable_t whitecap_enable : 1 = enable_t::disabled;
        scope_t scope : 2 = scope_t::global;
    private:
        u8 reserved_0 : 4 = 0;
        constant<u8, 0> reserved_1;
        constant<u16, 0> reserved_2;
    public:
        f32 sea_surface_height = 0.f;
        f32 surface_water_temperature = 0.f;
        bounded<f32, 0.f, 100.f> surface_clarity = 0.f;
    private:
        constant<u32, 0> reserved_3;
    };
};

inline auto operator <<(std::ostream& o, const cigi::maritime_surface_conditions_control& value) -> std::ostream&
{
    o << "maritime_surface_conditions_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity/region id: " << value.entity_id;
    o << "\n\tsurface_conditions_enable: " << value.surface_conditions_enable;
    o << "\n\twhitecap_enable: " << value.whitecap_enable;
    o << "\n\tscope: " << value.scope;
    o << "\n\tsea_surface_height: " << value.sea_surface_height;
    o << "\n\tsurface_water_temperature: " << value.surface_water_temperature;
    o << "\n\tsurface_clarity: " << value.surface_clarity;

    return o << "\n}";
};