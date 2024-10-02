#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.34
    struct alignas(std::uint64_t) symbol_control
    {
        enum class symbol_state_t : u8
        {
            hidden = 0,
            visible = 1,
            destroyed = 2,
        };
        enum class flash_control_t : u8
        {
            continue_ = 0,
            reset = 1,
        };

        constexpr symbol_control() = default;
        constexpr symbol_control(const symbol_control&) = default;
        constexpr symbol_control(symbol_control&&) noexcept = default;
        constexpr ~symbol_control() = default;
        constexpr auto operator =(const symbol_control& other) -> symbol_control&
        {
            symbol_id = other.symbol_id;
            symbol_state = other.symbol_state;
            attach_state = other.attach_state;
            flash_control = other.flash_control;
            inherit_color = other.inherit_color;
            parent_symbol_id = other.parent_symbol_id;
            surface_id = other.surface_id;
            layer = other.layer;
            flash_duty_cycle_percentage = other.flash_duty_cycle_percentage;
            flash_period = other.flash_period;
            position_u = other.position_u;
            position_v = other.position_v;
            rotation = other.rotation;
            red = other.red;
            green = other.green;
            blue = other.blue;
            alpha = other.alpha;
            scale_u = other.scale_u;
            scale_v = other.scale_v;

            return *this;
        };

        static auto serialize(const symbol_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, symbol_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 34> packet_id;
        constant<u8, 40> packet_size;
        u16 symbol_id = 0;
        symbol_state_t symbol_state : 2 = symbol_state_t::visible;
        attach_t attach_state : 1 = attach_t::detach;
        flash_control_t flash_control : 1 = flash_control_t::continue_;
        inherit_t inherit_color : 1 = inherit_t::not_inherited;
    private:
        u8 reserved_0 : 3 = 0;
        constant<u8, 0> reserved_1;
    public:
        u16 parent_symbol_id = 0;
        u16 surface_id = 0;
        u8 layer = 0;
        bounded<u8, 0, 100> flash_duty_cycle_percentage = 0;
        f32 flash_period = 0;
        f32 position_u = 0;
        f32 position_v = 0;
        bounded<f32, 0.f, 360.f> rotation = 0;
        u8 red = 0;
        u8 green = 0;
        u8 blue = 0;
        u8 alpha = 0;
        bounded<f32, 0.f> scale_u = 0;
        bounded<f32, 0.f> scale_v = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::symbol_control::flash_control_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_control::flash_control_t;
    case continue_:
        return o << "continue";
    case reset:
        return o << "reset";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_control::symbol_state_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_control::symbol_state_t;
    case visible:
        return o << "visible";
    case hidden:
        return o << "hidden";
    case destroyed:
        return o << "destroyed";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_control& value) -> std::ostream&
{
    o << "symbol_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tsymbol_id: " << value.symbol_id;
    o << "\n\tsymbol_state: " << value.symbol_state;
    o << "\n\tattach_state: " << value.attach_state;
    o << "\n\tflash_control: " << value.flash_control;
    o << "\n\tinherit_color: " << value.inherit_color;
    o << "\n\tparent_symbol_id: " << value.parent_symbol_id;
    o << "\n\tsurface_id: " << value.surface_id;
    o << "\n\tlayer: " << (int)value.layer;
    o << "\n\tflash_duty_cycle_percentage: " << (int)value.flash_duty_cycle_percentage.value;
    o << "\n\tflash_period: " << value.flash_period;
    o << "\n\tposition_u: " << value.position_u;
    o << "\n\tposition_v: " << value.position_v;
    o << "\n\trotation: " << value.rotation;
    o << "\n\tred: " << (int)value.red;
    o << "\n\tgreen: " << (int)value.green;
    o << "\n\tblue: " << (int)value.blue;
    o << "\n\talpha: " << (int)value.alpha;
    o << "\n\tscale_u: " << value.scale_u;
    o << "\n\tscale_v: " << value.scale_v;

    return o << "\n}";
};