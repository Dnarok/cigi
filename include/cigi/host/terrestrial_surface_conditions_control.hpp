#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.15
    struct alignas(std::uint64_t) alignas(std::uint32_t) terrestrial_surface_conditions_control
    {
        constexpr terrestrial_surface_conditions_control() = default;
        constexpr terrestrial_surface_conditions_control(const terrestrial_surface_conditions_control&) = default;
        constexpr terrestrial_surface_conditions_control(terrestrial_surface_conditions_control&&) noexcept = default;
        constexpr ~terrestrial_surface_conditions_control() = default;
        constexpr auto operator =(const terrestrial_surface_conditions_control& other) -> terrestrial_surface_conditions_control&
        {
            entity_id = other.entity_id;
            surface_condition_id = other.surface_condition_id;
            surface_condition_enable = other.surface_condition_enable;
            scope = other.scope;
            severity = other.severity;
            coverage = other.coverage;

            return *this;
        };

        static auto serialize(const terrestrial_surface_conditions_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, terrestrial_surface_conditions_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 15> packet_id;
        constant<u8, 8> packet_size;
        union
        {
            u16 entity_id = 0;
            u16 region_id;
        };
        u16 surface_condition_id = 0;
        enable_t surface_condition_enable : 1 = enable_t::disabled;
        scope_t scope : 2 = scope_t::global;
        u8 severity : 5 = 0;
        bounded<u8, 0, 100> coverage = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::terrestrial_surface_conditions_control& value) -> std::ostream&
{
    o << "terrestrial_surface_conditions_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity/region id: " << value.entity_id;
    o << "\n\tsurface_condition_id: " << value.surface_condition_id;
    o << "\n\tsurface_condition_enable: " << value.surface_condition_enable;
    o << "\n\tscope: " << value.scope;
    o << "\n\tseverity: " << (int)value.severity;
    o << "\n\tcoverage: " << (int)value.coverage.value;

    return o << "\n}";
};