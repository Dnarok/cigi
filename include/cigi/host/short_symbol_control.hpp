#pragma once

#include "general.hpp"
#include "symbol_control.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.35
    struct alignas(std::uint64_t) short_symbol_control
    {
        enum class attribute_select_t : u8
        {
            none = 0,
            surface_id = 1,
            parent_symbol_id = 2,
            layer = 3,
            flash_duty_cycle_percentage = 4,
            flash_period = 5,
            position_u = 6,
            position_v = 7,
            rotation = 8,
            color = 9,
            scale_u = 10,
            scale_v = 11,
        };
        union value_t
        {
            u32 integer = 0;
            f32 floating;
            struct
            {
                u8 red;
                u8 blue;
                u8 green;
                u8 alpha;
            };
        };

        constexpr short_symbol_control() = default;
        constexpr short_symbol_control(const short_symbol_control&) = default;
        constexpr short_symbol_control(short_symbol_control&&) noexcept = default;
        constexpr ~short_symbol_control() = default;
        constexpr auto operator =(const short_symbol_control& other) -> short_symbol_control&
        {
            symbol_id = other.symbol_id;
            symbol_state = other.symbol_state;
            attach_state = other.attach_state;
            flash_control = other.flash_control;
            inherit_color = other.inherit_color;
            attribute_select[0] = other.attribute_select[0];
            attribute_select[1] = other.attribute_select[1];
            attribute_values[0] = other.attribute_values[0];
            attribute_values[1] = other.attribute_values[1];

            return *this;
        };

        static auto serialize(const short_symbol_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, short_symbol_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 35> packet_id;
        constant<u8, 16> packet_size;
        u16 symbol_id = 0;
        symbol_control::symbol_state_t symbol_state : 2 = symbol_control::symbol_state_t::visible;
        attach_t attach_state : 1 = attach_t::detach;
        symbol_control::flash_control_t flash_control : 1 = symbol_control::flash_control_t::continue_;
        inherit_t inherit_color : 1 = inherit_t::not_inherited;
    private:
        u8 reserved_0 : 3 = 0;
        constant<u8, 0> reserved_1;
    public:
        attribute_select_t attribute_select[2] = {};
        value_t attribute_values[2] = {};

        auto set_surface_id(bounded<u8, 0, 1> index, u32 value) -> void
        {
            attribute_select[index] = attribute_select_t::surface_id;
            attribute_values[index].integer = value;
        };
        auto set_parent_symbol_id(bounded<u8, 0, 1> index, u32 value) -> void
        {
            attribute_select[index] = attribute_select_t::parent_symbol_id;
            attribute_values[index].integer = value;
        };
        auto set_layer(bounded<u8, 0, 1> index, u32 value) -> void
        {
            attribute_select[index] = attribute_select_t::layer;
            attribute_values[index].integer = value;
        };
        auto set_flash_duty_cycle_percentage(bounded<u8, 0, 1> index, u32 value) -> void
        {
            attribute_select[index] = attribute_select_t::flash_duty_cycle_percentage;
            attribute_values[index].integer = value;
        };

        auto set_flash_period(bounded<u8, 0, 1> index, f32 value) -> void
        {
            attribute_select[index] = attribute_select_t::flash_period;
            attribute_values[index].floating = value;
        };
        auto set_position_u(bounded<u8, 0, 1> index, f32 value) -> void
        {
            attribute_select[index] = attribute_select_t::position_u;
            attribute_values[index].floating = value;
        };
        auto set_position_v(bounded<u8, 0, 1> index, f32 value) -> void
        {
            attribute_select[index] = attribute_select_t::position_v;
            attribute_values[index].floating = value;
        };
        auto set_rotation(bounded<u8, 0, 1> index, f32 value) -> void
        {
            attribute_select[index] = attribute_select_t::rotation;
            attribute_values[index].floating = value;
        };
        auto set_scale_u(bounded<u8, 0, 1> index, f32 value) -> void
        {
            attribute_select[index] = attribute_select_t::scale_u;
            attribute_values[index].floating = value;
        };
        auto set_scale_v(bounded<u8, 0, 1> index, f32 value) -> void
        {
            attribute_select[index] = attribute_select_t::scale_v;
            attribute_values[index].floating = value;
        };

        auto set_color(bounded<u8, 0, 1> index, u8 red, u8 blue, u8 green, u8 alpha) -> void
        {
            attribute_select[index] = attribute_select_t::color;
            attribute_values[index].red = red;
            attribute_values[index].blue = blue;
            attribute_values[index].green = green;
            attribute_values[index].alpha = alpha;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::short_symbol_control::attribute_select_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::short_symbol_control::attribute_select_t;
    case none:
        return o << "none";
    case surface_id:
        return o << "surface id";
    case parent_symbol_id:
        return o << "parent symbol id";
    case layer:
        return o << "layer";
    case flash_duty_cycle_percentage:
        return o << "flash duty cycle percentage";
    case flash_period:
        return o << "flash period";
    case position_u:
        return o << "position u";
    case position_v:
        return o << "position v";
    case rotation:
        return o << "rotation";
    case color:
        return o << "color";
    case scale_u:
        return o << "scale u";
    case scale_v:
        return o << "scale v";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::short_symbol_control& value) -> std::ostream&
{
    o << "short_symbol_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tsymbol_id: " << value.symbol_id;
    o << "\n\tsymbol_state: " << value.symbol_state;
    o << "\n\tattach_state: " << value.attach_state;
    o << "\n\tflash_control: " << value.flash_control;
    o << "\n\tinherit_color: " << value.inherit_color;
    o << "\n\tattributes: ";
    o << "\n\t  0: ";
    o << "\n\t    attribute_select: " << value.attribute_select[0];
    o << "\n\t    attribute_value: ";
    switch (value.attribute_select[0])
    {
    using enum cigi::short_symbol_control::attribute_select_t;
    default:
    case none:
        o << "n/a (" << value.attribute_values[0].integer << ')';
        break;
    case surface_id:
    case parent_symbol_id:
    case layer:
    case flash_duty_cycle_percentage:
        o << value.attribute_values[0].integer;
        break;
    case flash_period:
    case position_u:
    case position_v:
    case rotation:
    case scale_u:
    case scale_v:
        o << value.attribute_values[0].floating;
        break;
    case color:
        o << "r: " << (int)value.attribute_values[0].red
         << " b: " << (int)value.attribute_values[0].blue
         << " g: " << (int)value.attribute_values[0].green
         << " a: " << (int)value.attribute_values[0].alpha;
        break;
    }
    o << "\n\t  1: ";
    o << "\n\t    attribute_select: " << value.attribute_select[1];
    o << "\n\t    attribute_value: ";
    switch (value.attribute_select[1])
    {
    using enum cigi::short_symbol_control::attribute_select_t;
    default:
    case none:
        o << "n/a (" << value.attribute_values[1].integer << ')';
        break;
    case surface_id:
    case parent_symbol_id:
    case layer:
    case flash_duty_cycle_percentage:
        o << value.attribute_values[1].integer;
        break;
    case flash_period:
    case position_u:
    case position_v:
    case rotation:
    case scale_u:
    case scale_v:
        o << value.attribute_values[1].floating;
        break;
    case color:
        o << "r: " << (int)value.attribute_values[1].red
         << " b: " << (int)value.attribute_values[1].blue
         << " g: " << (int)value.attribute_values[1].green
         << " a: " << (int)value.attribute_values[1].alpha;
        break;
    }

    return o << "\n}";
};