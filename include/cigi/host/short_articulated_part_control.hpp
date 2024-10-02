#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 §4.1.7
    struct alignas(std::uint64_t) short_articulated_part_control
    {
        enum class dof_select_t : u8
        {
            not_used = 0,
            x_offset = 1,
            y_offset = 2,
            z_offset = 3,
            yaw = 4,
            pitch = 5,
            roll = 6,
        };
        union dof_t
        {
            f32 x_offset = 0.f;
            f32 y_offset;
            f32 z_offset;
            bounded<f32, 0.f, 360.f> yaw;
            bounded<f32, -90.f, 90.f> pitch;
            bounded<f32, -180.f, 180.f> roll;
        };

        constexpr short_articulated_part_control() = default;
        constexpr short_articulated_part_control(const short_articulated_part_control&) = default;
        constexpr short_articulated_part_control(short_articulated_part_control&&) noexcept = default;
        constexpr ~short_articulated_part_control() = default;
        constexpr auto operator =(const short_articulated_part_control& other) -> short_articulated_part_control&
        {
            entity_id = other.entity_id;
            articulated_part_id[0] = other.articulated_part_id[0];
            articulated_part_id[1] = other.articulated_part_id[1];
            dof_select_1 = other.dof_select_1;
            dof_select_2 = other.dof_select_2;
            articulated_part_enable_1 = other.articulated_part_enable_1;
            articulated_part_enable_2 = other.articulated_part_enable_2;
            dof[0] = other.dof[0];
            dof[1] = other.dof[1];

            return *this;
        };

        static auto serialize(const short_articulated_part_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, short_articulated_part_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 7> packet_id;
        constant<u8, 16> packet_size;
        u16 entity_id = 0;
        u8 articulated_part_id[2] = { 0, 0 };
        dof_select_t dof_select_1 : 3 = dof_select_t::not_used;
        dof_select_t dof_select_2 : 3 = dof_select_t::not_used;
        enable_t articulated_part_enable_1 : 1 = enable_t::disabled;
        enable_t articulated_part_enable_2 : 1 = enable_t::disabled;
    private:
        constant<u8, 0> reserved_0;
    public:
        dof_t dof[2] = {};
    };
};


inline auto operator <<(std::ostream& o, const cigi::short_articulated_part_control::dof_select_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::short_articulated_part_control::dof_select_t;
    case not_used:
        return o << "not used";
    case x_offset:
        return o << "x offset";
    case y_offset:
        return o << "y offset";
    case z_offset:
        return o << "z offset";
    case yaw:
        return o << "yaw";
    case pitch:
        return o << "pitch";
    case roll:
        return o << "roll";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::short_articulated_part_control& value) -> std::ostream&
{
    o << "short_articulated_part_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tentity_id: " << value.entity_id;
    o << "\n\tarticulated_part_id_1: " << (int)value.articulated_part_id[0];
    o << "\n\tarticulated_part_id_2: " << (int)value.articulated_part_id[1];
    o << "\n\tdof_select_1: " << value.dof_select_1;
    o << "\n\tdof_select_2: " << value.dof_select_2;
    o << "\n\tarticulated_part_enable_1: " << value.articulated_part_enable_1;
    o << "\n\tarticulated_part_enable_2: " << value.articulated_part_enable_2;
    o << "\n\tdof_1: " << value.dof[0].x_offset;
    o << "\n\tdof_2: " << value.dof[1].x_offset;

    return o << "\n}";
};