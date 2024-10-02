#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.29
    struct alignas(std::uint64_t) symbol_surface_definition
    {
        enum class state_t : u8
        {
            active = 0,
            destroyed = 1,
        };
        enum class attach_t : u8
        {
            entity = 0,
            view = 1,
        };
        enum class billboard_t : u8
        {
            non_billboard = 0,
            billboard = 1,
        };

        constexpr symbol_surface_definition() = default;
        constexpr symbol_surface_definition(const symbol_surface_definition&) = default;
        constexpr symbol_surface_definition(symbol_surface_definition&&) noexcept = default;
        constexpr ~symbol_surface_definition() = default;
        constexpr auto operator =(const symbol_surface_definition& other) -> symbol_surface_definition&
        {
            surface_id = other.surface_id;
            surface_state = other.surface_state;
            attach_type = other.attach_type;
            billboard = other.billboard;
            perspective_growth_enable = other.perspective_growth_enable;
            entity_id = other.entity_id;
            x_offset = other.x_offset;
            y_offset = other.y_offset;
            z_offset = other.z_offset;
            yaw = other.yaw;
            pitch = other.pitch;
            roll = other.roll;
            width = other.width;
            height = other.height;
            min_u = other.min_u;
            max_u = other.max_u;
            min_v = other.min_v;
            max_v = other.max_v;

            return *this;
        };

        static auto serialize(const symbol_surface_definition& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, symbol_surface_definition& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 29> packet_id;
        constant<u8, 56> packet_size;
        u16 surface_id = 0;
        state_t surface_state : 1 = state_t::active;
        attach_t attach_type : 1 = attach_t::entity;
        billboard_t billboard : 1 = billboard_t::non_billboard;
        enable_t perspective_growth_enable : 1 = enable_t::disabled;
    private:
        u8 reserved_0 : 3 = 0;
        constant<u8, 0> reserved_1;
    public:
        union
        {
            u16 entity_id = 0;
            u16 view_id;
        };
        union
        {
            f32 x_offset = 0.f;
            f32 left;
        };
        union
        {
            f32 y_offset = 0.f;
            f32 right;
        };
        union
        {
            f32 z_offset = 0.f;
            f32 top;
        };
        union
        {
            bounded<f32, 0.f, 360.f> yaw = 0.f;
            f32 bottom;
        };
        bounded<f32, -90.f, 90.f> pitch = 0.f;
        bounded<f32, -180.f, 180.f> roll = 0.f;
        bounded<f32, 0.f> width = 0.f;
        bounded<f32, 0.f> height = 0.f;
        f32 min_u = 0.f;
        f32 max_u = 0.f;
        f32 min_v = 0.f;
        f32 max_v = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::symbol_surface_definition::state_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_surface_definition::state_t;
    case active:
        return o << "active";
    case destroyed:
        return o << "destroyed";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_surface_definition::attach_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_surface_definition::attach_t;
    case entity:
        return o << "entity";
    case view:
        return o << "view";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_surface_definition::billboard_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_surface_definition::billboard_t;
    case non_billboard:
        return o << "non-billboard";
    case billboard:
        return o << "billboard";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_surface_definition& value) -> std::ostream&
{
    o << "symbol_surface_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tsurface_id: " << value.surface_id;
    o << "\n\tsurface_state: " << value.surface_state;
    o << "\n\tattach_type: " << value.attach_type;
    o << "\n\tbillboard: " << value.billboard;
    o << "\n\tperspective_growth_enable: " << value.perspective_growth_enable;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tx_offset: " << value.x_offset;
    o << "\n\ty_offset: " << value.y_offset;
    o << "\n\tz_offset: " << value.z_offset;
    o << "\n\tyaw: " << value.yaw;
    o << "\n\tpitch: " << value.pitch;
    o << "\n\troll: " << value.roll;
    o << "\n\twidth: " << value.width;
    o << "\n\theight: " << value.height;
    o << "\n\tmin_u: " << value.min_u;
    o << "\n\tmax_u: " << value.max_u;
    o << "\n\tmin_v: " << value.min_v;
    o << "\n\tmax_v: " << value.max_v;

    return o << "\n}";
};