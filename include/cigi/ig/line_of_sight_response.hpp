#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.4
    struct line_of_sight_response
    {
        enum class visible_t : u8
        {
            occluded = 0,
            visible = 1,
        };

        constexpr line_of_sight_response() = default;
        constexpr line_of_sight_response(const line_of_sight_response&) = default;
        constexpr line_of_sight_response(line_of_sight_response&&) noexcept = default;
        constexpr ~line_of_sight_response() = default;
        constexpr auto operator =(const line_of_sight_response& other) -> line_of_sight_response&
        {
            los_id = other.los_id;
            valid = other.valid;
            entity_id_valid = other.entity_id_valid;
            visible = other.visible;
            host_frame_number_lsn = other.host_frame_number_lsn;
            response_count = other.response_count;
            entity_id = other.entity_id;
            range = other.range;

            return *this;
        };

        static auto serialize(const line_of_sight_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, line_of_sight_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 104> packet_id;
        constant<u8, 16> packet_size;
        u16 los_id = 0;
        valid_t valid : 1 = valid_t::invalid;
        valid_t entity_id_valid : 1 = valid_t::invalid;
        visible_t visible : 1 = visible_t::occluded;
    private:
        u8 reserved_0 : 1 = 0;
    public:
        u8 host_frame_number_lsn : 4 = 0;
        u8 response_count = 0;
        u16 entity_id = 0;
        f64 range = 0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::line_of_sight_response::visible_t& value) -> ostream&
{
    switch (value)
    {
    using enum cigi::line_of_sight_response::visible_t;
    case occluded:
        return o << "occluded";
    case visible:
        return o << "visible";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::line_of_sight_response& value) -> ostream&
{
    o << "line_of_sight_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tlos_id: " << value.los_id;
    o << "\n\tvalid: " << value.valid;
    o << "\n\tentity_id_valid: " << value.entity_id_valid;
    o << "\n\tvisible: " << value.visible;
    o << "\n\thost_frame_number_lsn: " << (int)value.host_frame_number_lsn;
    o << "\n\tresponse_count: " << (int)value.response_count;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\trange: " << value.range;

    return o << "\n}";
};