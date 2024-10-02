#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.22
    struct alignas(std::uint64_t) collision_detection_segment_definition
    {
        constexpr collision_detection_segment_definition() = default;
        constexpr collision_detection_segment_definition(const collision_detection_segment_definition&) = default;
        constexpr collision_detection_segment_definition(collision_detection_segment_definition&&) noexcept = default;
        constexpr ~collision_detection_segment_definition() = default;
        constexpr auto operator =(const collision_detection_segment_definition& other) -> collision_detection_segment_definition&
        {
            entity_id = other.entity_id;
            segment_id = other.segment_id;
            segment_enable = other.segment_enable;
            x1 = other.x1;
            y1 = other.y1;
            z1 = other.z1;
            x2 = other.x2;
            y2 = other.y2;
            z2 = other.z2;
            material_mask = other.material_mask;

            return *this;
        };

        static auto serialize(const collision_detection_segment_definition& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, collision_detection_segment_definition& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 22> packet_id;
        constant<u8, 40> packet_size;
        u16 entity_id = 0;
        u8 segment_id = 0;
        enable_t segment_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_0 : 7 = 0;
        constant<u16, 0> reserved_1;
    public:
        f32 x1 = 0.f;
        f32 y1 = 0.f;
        f32 z1 = 0.f;
        f32 x2 = 0.f;
        f32 y2 = 0.f;
        f32 z2 = 0.f;
        u32 material_mask = 0;
    private:
        constant<u32, 0> reserved_2;
    };
};

inline auto operator <<(std::ostream& o, const cigi::collision_detection_segment_definition& value) -> std::ostream&
{
    o << "collision_detection_segment_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tsegment_id: " << (int)value.segment_id;
    o << "\n\tsegment_enable: " << value.segment_enable;
    o << "\n\tx1: " << value.x1;
    o << "\n\ty1: " << value.y1;
    o << "\n\tz1: " << value.z1;
    o << "\n\tx2: " << value.x2;
    o << "\n\ty2: " << value.y2;
    o << "\n\tz2: " << value.z2;
    o << "\n\tmaterial_mask: " << value.material_mask;

    return o << "\n}";
};