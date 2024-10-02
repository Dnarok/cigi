#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.2
    struct hat_hot_response
    {
        enum class response_type_t : u8
        {
            hat = 0,
            hot = 1,
        };

        constexpr hat_hot_response() = default;
        constexpr hat_hot_response(const hat_hot_response&) = default;
        constexpr hat_hot_response(hat_hot_response&&) noexcept = default;
        constexpr ~hat_hot_response() = default;
        constexpr auto operator =(const hat_hot_response& other) -> hat_hot_response&
        {
            hat_hot_id = other.hat_hot_id;
            valid = other.valid;
            response_type = other.response_type;
            host_frame_number_lsn = other.host_frame_number_lsn;
            height = other.height;

            return *this;
        };

        static auto serialize(const hat_hot_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, hat_hot_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 102> packet_id;
        constant<u8, 16> packet_size;
        u16 hat_hot_id = 0;
        valid_t valid : 1 = valid_t::invalid;
        response_type_t response_type : 1 = response_type_t::hat;
    private:
        u8 reserved_0 : 2 = 0;
    public:
        u8 host_frame_number_lsn : 4 = 0;
    private:
        constant<u8, 0> reserved_1;
        constant<u16, 0> reserved_2;
    public:
        f64 height = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::hat_hot_response::response_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::hat_hot_response::response_type_t;
    case hat:
        return o << "HAT";
    case hot:
        return o << "HOT";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::hat_hot_response& value) -> ostream&
{
    o << "hat_hot_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\that_hot_id: " << value.hat_hot_id;
    o << "\n\tvalid: " << value.valid;
    o << "\n\tresponse_type: " << value.response_type;
    o << "\n\thost_frame_number_lsn: " << (int)value.host_frame_number_lsn;
    o << "\n\theight: " << value.height;

    return o << "\n}";
};