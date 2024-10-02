#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.23
    struct alignas(std::uint64_t) collision_detection_volume_definition
    {
        enum class volume_type_t : u8
        {
            sphere = 0,
            cuboid = 1,
        };

        constexpr collision_detection_volume_definition() = default;
        constexpr collision_detection_volume_definition(const collision_detection_volume_definition&) = default;
        constexpr collision_detection_volume_definition(collision_detection_volume_definition&&) noexcept = default;
        constexpr ~collision_detection_volume_definition() = default;
        constexpr auto operator =(const collision_detection_volume_definition& other) -> collision_detection_volume_definition&
        {
            entity_id = other.entity_id;
            volume_id = other.volume_id;
            volume_enable = other.volume_enable;
            volume_type = other.volume_type;
            x = other.x;
            y = other.y;
            z = other.z;
            height = other.height;
            width = other.width;
            depth = other.depth;
            roll = other.roll;
            pitch = other.pitch;
            yaw = other.yaw;

            return *this;
        };

        static auto serialize(const collision_detection_volume_definition& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, collision_detection_volume_definition& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 23> packet_id;
        constant<u8, 48> packet_size;
        u16 entity_id = 0;
        u8 volume_id = 0;
        enable_t volume_enable : 1 = enable_t::disabled;
        volume_type_t volume_type : 1 = volume_type_t::sphere;
    private:
        u8 reserved_0 : 6 = 0;
        constant<u16, 0> reserved_1;
    public:
        f32 x = 0.f;
        f32 y = 0.f;
        f32 z = 0.f;
        union
        {
            bounded<f32, 0.f> height = 0.f;
            bounded<f32, 0.f> radius;
        };
        bounded<f32, 0.f> width = 0.f;
        bounded<f32, 0.f> depth = 0.f;
        bounded<f32, -180.f, 180.f> roll = 0.f;
        bounded<f32, -90.f, 90.f> pitch = 0.f;
        bounded<f32, 0.f, 360.f> yaw = 0.f;
    private:
        constant<u32, 0> reserved_2;
    };
};

inline auto operator <<(std::ostream& o, const cigi::collision_detection_volume_definition::volume_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::collision_detection_volume_definition::volume_type_t;
    case sphere:
        return o << "sphere";
    case cuboid:
        return o << "cuboid";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::collision_detection_volume_definition& value) -> std::ostream&
{
    o << "collision_detection_volume_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tvolume_id: " << (int)value.volume_id;
    o << "\n\tvolume_enable: " << value.volume_enable;
    o << "\n\tvolume_type: " << value.volume_type;
    o << "\n\tx: " << value.x;
    o << "\n\ty: " << value.y;
    o << "\n\tz: " << value.z;
    o << "\n\theight: " << value.height;
    o << "\n\twidth: " << value.width;
    o << "\n\tdepth: " << value.depth;
    o << "\n\troll: " << value.roll;
    o << "\n\tpitch: " << value.pitch;
    o << "\n\tyaw: " << value.yaw;

    return o << "\n}";
};