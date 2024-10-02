#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.15
    struct alignas(std::uint64_t) animation_stop_notification
    {
        constexpr animation_stop_notification() = default;
        constexpr animation_stop_notification(const animation_stop_notification&) = default;
        constexpr animation_stop_notification(animation_stop_notification&&) noexcept = default;
        constexpr ~animation_stop_notification() = default;
        constexpr auto operator =(const animation_stop_notification& other) -> animation_stop_notification&
        {
            entity_id = other.entity_id;

            return *this;
        };

        static auto serialize(const animation_stop_notification& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, animation_stop_notification& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 115> packet_id;
        constant<u8, 8> packet_size;
        u16 entity_id = 0;
    private:
        constant<u32, 0> reserved_0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::animation_stop_notification& value) -> ostream&
{
    o << "animation_stop_notification {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;

    return o << "\n}";
};