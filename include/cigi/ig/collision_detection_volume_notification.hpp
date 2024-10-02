#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.14
    struct alignas(std::uint64_t) collision_detection_volume_notification
    {
        constexpr collision_detection_volume_notification() = default;
        constexpr collision_detection_volume_notification(const collision_detection_volume_notification&) = default;
        constexpr collision_detection_volume_notification(collision_detection_volume_notification&&) noexcept = default;
        constexpr ~collision_detection_volume_notification() = default;
        constexpr auto operator =(const collision_detection_volume_notification& other) -> collision_detection_volume_notification&
        {
            entity_id = other.entity_id;
            volume_id = other.volume_id;
            collision_type = other.collision_type;
            contacted_entity_id = other.contacted_entity_id;
            contacted_volume_id = other.contacted_volume_id;

            return *this;
        };

        static auto serialize(const collision_detection_volume_notification& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, collision_detection_volume_notification& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 114> packet_id;
        constant<u8, 16> packet_size;
        u16 entity_id = 0;
        u8 volume_id = 0;
        collision_t collision_type : 1 = collision_t::non_entity;
    private:
        u8 reserved_0 : 7 = 0;
    public:
        u16 contacted_entity_id = 0;
        u8 contacted_volume_id = 0;
    private:
        constant<u8, 0> reserved_1[3];
        constant<u32, 0> reserved_2;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::collision_detection_volume_notification& value) -> ostream&
{
    o << "collision_detection_volume_notification {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tvolume_id: " << (int)value.volume_id;
    o << "\n\tcollision_type: " << value.collision_type;
    o << "\n\tcontacted_entity_id: " << value.contacted_entity_id;
    o << "\n\tcontacted_volume_id: " << (int)value.contacted_volume_id;

    return o << "\n}";
};

/*
entity_id
volume_id
collision_type
contacted_entity_id
contacted_volume_id
*/