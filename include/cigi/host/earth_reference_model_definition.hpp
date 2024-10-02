#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.19
    struct earth_reference_model_definition
    {
        constexpr earth_reference_model_definition() = default;
        constexpr earth_reference_model_definition(const earth_reference_model_definition&) = default;
        constexpr earth_reference_model_definition(earth_reference_model_definition&&) noexcept = default;
        constexpr ~earth_reference_model_definition() = default;
        constexpr auto operator =(const earth_reference_model_definition& other) -> earth_reference_model_definition&
        {
            custom_erm_enable = other.custom_erm_enable;
            equatorial_radius = other.equatorial_radius;
            flattening = other.flattening;

            return *this;
        };

        static auto serialize(const earth_reference_model_definition& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, earth_reference_model_definition& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 19> packet_id;
        constant<u8, 24> packet_size;
        enable_t custom_erm_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_0 : 7 = 0;
        constant<u8, 0> reserved_1;
        constant<u32, 0> reserved_2;
    public:
        f64 equatorial_radius = 6'378'137.0;
        f64 flattening = 1.0 / 298.257'223'563;
    };
};

inline auto operator <<(std::ostream& o, const cigi::earth_reference_model_definition& value) -> std::ostream&
{
    o << "earth_reference_model_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tcustom_erm_enable: " << value.custom_erm_enable;
    o << "\n\tequatorial_radius: " << value.equatorial_radius;
    o << "\n\tflattening: " << value.flattening;

    return o << "\n}";
};