#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.9
    struct alignas(std::uint64_t) celestial_sphere_control
    {
        constexpr celestial_sphere_control() = default;
        constexpr celestial_sphere_control(const celestial_sphere_control&) = default;
        constexpr celestial_sphere_control(celestial_sphere_control&&) noexcept = default;
        constexpr ~celestial_sphere_control() = default;
        constexpr auto operator =(const celestial_sphere_control& other) -> celestial_sphere_control&
        {
            hour = other.hour;
            minute = other.minute;
            ephemeris_model_enable = other.ephemeris_model_enable;
            sun_enable = other.sun_enable;
            moon_enable = other.moon_enable;
            star_field_enable = other.star_field_enable;
            date_time_valid = other.date_time_valid;
            date = other.date;
            star_field_intensity = other.star_field_intensity;

            return *this;
        };

        static auto serialize(const celestial_sphere_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, celestial_sphere_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 9> packet_id;
        constant<u8, 16> packet_size;
        bounded<u8, 0, 23> hour = 0;
        bounded<u8, 0, 59> minute = 0;
        enable_t ephemeris_model_enable : 1 = enable_t::enabled;
        enable_t sun_enable : 1 = enable_t::disabled;
        enable_t moon_enable : 1 = enable_t::disabled;
        enable_t star_field_enable : 1 = enable_t::disabled;
        valid_t date_time_valid : 1 = valid_t::invalid;
    private:
        u8 reserved_0 : 3 = 0;
        u8 reserved_1 = 0;
        u16 reserved_2 = 0;
    public:
        u32 date = 1011970;
        bounded<f32, 0.f, 100.f> star_field_intensity = 0.f;

        auto set_date(bounded<u8, 1, 31> day = 1, bounded<u8, 1, 12> month = 1, bounded<u16, 0, 9999> year = 1970)
        {
            date = month * 1'000'000
                 + day   * 10'000
                 + year;
        };
        auto get_year() const -> bounded<u16, 0, 9999>
        {
            return date % 10'000;
        };
        auto get_month() const -> bounded<u8, 1, 12>
        {
            return date / 1'000'000;
        };
        auto get_day() const -> bounded<u8, 1, 31>
        {
            return (date / 10'000) % 100;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::celestial_sphere_control& value) -> std::ostream&
{
    o << "celestial_sphere_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\thour: " << (int)value.hour.value;
    o << "\n\tminute: " << (int)value.minute.value;
    o << "\n\tephemeris_model_enable: " << value.ephemeris_model_enable;
    o << "\n\tsun_enable: " << value.sun_enable;
    o << "\n\tmoon_enable: " << value.moon_enable;
    o << "\n\tstar_field_enable: " << value.star_field_enable;
    o << "\n\tdate_time_valid: " << value.date_time_valid;
    o << "\n\tdate: " << value.date;
    o << "\n\t\tday: " << (int)value.get_day().value;
    o << "\n\t\tmonth: " << (int)value.get_month().value;
    o << "\n\t\tyear: " << value.get_year();
    o << "\n\tstar_field_intensity: " << value.star_field_intensity;

    return o << "\n}";
};