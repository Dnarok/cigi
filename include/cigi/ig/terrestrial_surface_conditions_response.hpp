#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.12
    struct alignas(std::uint64_t) terrestrial_surface_conditions_response
    {
        constexpr terrestrial_surface_conditions_response() = default;
        constexpr terrestrial_surface_conditions_response(const terrestrial_surface_conditions_response&) = default;
        constexpr terrestrial_surface_conditions_response(terrestrial_surface_conditions_response&&) noexcept = default;
        constexpr ~terrestrial_surface_conditions_response() = default;
        constexpr auto operator =(const terrestrial_surface_conditions_response& other) -> terrestrial_surface_conditions_response&
        {
            request_id = other.request_id;
            surface_condition_id = other.surface_condition_id;

            return *this;
        };

        static auto serialize(const terrestrial_surface_conditions_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, terrestrial_surface_conditions_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 112> packet_id;
        constant<u8, 8> packet_size;
        u8 request_id = 0;
    private:
        constant<u8, 0> reserved_0;
    public:
        bounded<u32, 0, 65'535> surface_condition_id = 0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::terrestrial_surface_conditions_response& value) -> ostream&
{
    o << "terrestrial_surface_conditions_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\trequest_id: " << (int)value.request_id;
    o << "\n\tsurface_condition_id: " << value.surface_condition_id;

    return o << "\n}";
};