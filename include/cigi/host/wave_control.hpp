#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.14
    struct alignas(std::uint64_t) wave_control
    {
        enum class breaker_type_t : u8
        {
            plunging = 0,
            spilling = 1,
            surging = 2,
        };

        constexpr wave_control() = default;
        constexpr wave_control(const wave_control&) = default;
        constexpr wave_control(wave_control&&) noexcept = default;
        constexpr ~wave_control() = default;
        constexpr auto operator =(const wave_control& other) -> wave_control&
        {


            return *this;
        };

        static auto serialize(const wave_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, wave_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 14> packet_id;
        constant<u8, 32> packet_size;
        union
        {
            u16 entity_id = 0;
            u16 region_id;
        };
        u8 wave_id = 0;
        enable_t wave_enable : 1 = enable_t::disabled;
        scope_t scope : 2 = scope_t::global;
        breaker_type_t breaker_type : 2 = breaker_type_t::plunging;
    private:
        u8 reserved_0 : 3 = 0;
        constant<u16, 0> reserved_1;
    public:
        bounded<f32, 0.f> wave_height = 0.f;
        bounded<f32, 0.f> wavelength = 0.f;
        bounded<f32, 0.f> period = 0.f;
        bounded<f32, 0.f, 360.f> direction = 0.f;
        bounded<f32, -360.f, 360.f> phase_offset = 0.f;
        bounded<f32, -180.f, 180.f> leading = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::wave_control::breaker_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::wave_control::breaker_type_t;
    case plunging:
        return o << "plunging";
    case spilling:
        return o << "spilling";
    case surging:
        return o << "surging";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::wave_control& value) -> std::ostream&
{
    o << "wave_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity/region id: " << value.entity_id;
    o << "\n\twave_id: " << (int)value.wave_id;
    o << "\n\twave_enable: " << value.wave_enable;
    o << "\n\tscope: " << value.scope;
    o << "\n\tbreaker_type: " << value.breaker_type;
    o << "\n\twave_height: " << value.wave_height;
    o << "\n\twavelength: " << value.wavelength;
    o << "\n\tperiod: " << value.period;
    o << "\n\tdirection: " << value.direction;
    o << "\n\tphase_offset: " << value.phase_offset;
    o << "\n\tleading: " << value.leading;

    return o << "\n}";
};