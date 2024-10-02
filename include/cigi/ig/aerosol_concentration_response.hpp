#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.10
    struct alignas(std::uint64_t) aerosol_concentration_response
    {
        constexpr aerosol_concentration_response() = default;
        constexpr aerosol_concentration_response(const aerosol_concentration_response&) = default;
        constexpr aerosol_concentration_response(aerosol_concentration_response&&) noexcept = default;
        constexpr ~aerosol_concentration_response() = default;
        constexpr auto operator =(const aerosol_concentration_response& other) -> aerosol_concentration_response&
        {
            request_id = other.request_id;
            layer_id = other.layer_id;
            aerosol_concentration = other.aerosol_concentration;

            return *this;
        };

        static auto serialize(const aerosol_concentration_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, aerosol_concentration_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 110> packet_id;
        constant<u8, 8> packet_size;
        u8 request_id = 0;
        u8 layer_id = 0;
        bounded<f32, 0.f> aerosol_concentration = 0.f;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::aerosol_concentration_response& value) -> ostream&
{
    o << "aerosol_concentration_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\trequest_id: " << (int)value.request_id;
    o << "\n\tlayer_id: " << (int)value.layer_id;
    o << "\n\taerosol_concentration: " << value.aerosol_concentration;

    return o << "\n}";
};