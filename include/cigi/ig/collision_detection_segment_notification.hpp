#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.13
    struct alignas(std::uint64_t) collision_detection_segment_notification
    {
        constexpr collision_detection_segment_notification() = default;
        constexpr collision_detection_segment_notification(const collision_detection_segment_notification&) = default;
        constexpr collision_detection_segment_notification(collision_detection_segment_notification&&) noexcept = default;
        constexpr ~collision_detection_segment_notification() = default;
        constexpr auto operator =(const collision_detection_segment_notification& other) -> collision_detection_segment_notification&
        {
            entity_id = other.entity_id;
            segment_id = other.segment_id;
            collision_type = other.collision_type;
            contacted_entity_id = other.contacted_entity_id;
            material_code = other.material_code;
            intersection_distance = other.intersection_distance;

            return *this;
        };

        static auto serialize(const collision_detection_segment_notification& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, collision_detection_segment_notification& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 113> packet_id;
        constant<u8, 16> packet_size;
        u16 entity_id = 0;
        u8 segment_id = 0;
        collision_t collision_type : 1 = collision_t::non_entity;
    private:
        u8 reserved_0 : 7 = 0;
    public:
        u16 contacted_entity_id = 0;
        u32 material_code = 0;
        f32 intersection_distance = 0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::collision_detection_segment_notification& value) -> ostream&
{
    o << "collision_detection_segment_notification {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tsegment_id: " << (int)value.segment_id;
    o << "\n\tcollision_type: " << value.collision_type;
    o << "\n\tcontacted_entity_id: " << value.contacted_entity_id;
    o << "\n\tmaterial_code: " << value.material_code;
    o << "\n\tintersection_distance: " << value.intersection_distance;

    return o << "\n}";
};