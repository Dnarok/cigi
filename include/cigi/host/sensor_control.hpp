#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.17
    struct alignas(std::uint64_t) sensor_control
    {
        enum class on_off_t : u8
        {
            off = 0,
            on = 1,
        };
        enum class polarity_t : u8
        {
            white_hot = 0,
            black_hot = 1,
        };
        enum class track_white_black_t : u8
        {
            white = 0,
            black = 1,
        };
        enum class response_type_t : u8
        {
            normal = 0,
            extended = 1,
        };
        enum class track_mode_t : u8
        {
            off = 0,
            force_correlate = 1,
            scene = 2,
            target = 3,
            ship = 4,
        };

        constexpr sensor_control() = default;
        constexpr sensor_control(const sensor_control&) = default;
        constexpr sensor_control(sensor_control&&) noexcept = default;
        constexpr ~sensor_control() = default;
        constexpr auto operator =(const sensor_control& other) -> sensor_control&
        {
            view_id = other.view_id;
            sensor_id = other.sensor_id;
            sensor_on_off = other.sensor_on_off;
            polarity = other.polarity;
            line_by_line_dropout_enable = other.line_by_line_dropout_enable;
            automatic_gain = other.automatic_gain;
            track_white_black = other.track_white_black;
            track_mode = other.track_mode;
            response_type = other.response_type;
            gain = other.gain;
            level = other.level;
            ac_coupling = other.ac_coupling;
            noise = other.noise;

            return *this;
        };

        static auto serialize(const sensor_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, sensor_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 17> packet_id;
        constant<u8, 24> packet_size;
        u16 view_id = 0;
        u8 sensor_id = 0;
        on_off_t sensor_on_off : 1 = on_off_t::off;
        polarity_t polarity : 1 = polarity_t::white_hot;
        enable_t line_by_line_dropout_enable : 1 = enable_t::disabled;
        enable_t automatic_gain : 1 = enable_t::disabled;
        track_white_black_t track_white_black : 1 = track_white_black_t::white;
        track_mode_t track_mode : 3 = track_mode_t::off;
        response_type_t response_type : 1 = response_type_t::normal;
    private:
        u8 reserved_0 : 7 = 0;
        constant<u8, 0> reserved_1;
    public:
        bounded<f32, 0.f, 1.f> gain = 0;
        bounded<f32, 0.f, 1.f> level = 0;
        bounded<f32, 0.f> ac_coupling = 0;
        bounded<f32, 0.f, 1.f> noise = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::sensor_control::on_off_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::sensor_control::on_off_t;
    case off:
        return o << "off";
    case on:
        return o << "on";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::sensor_control::polarity_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::sensor_control::polarity_t;
    case white_hot:
        return o << "white hot";
    case black_hot:
        return o << "black hot";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::sensor_control::track_white_black_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::sensor_control::track_white_black_t;
    case white:
        return o << "white";
    case black:
        return o << "black";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::sensor_control::response_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::sensor_control::response_type_t;
    case normal:
        return o << "normal";
    case extended:
        return o << "extended";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::sensor_control::track_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::sensor_control::track_mode_t;
    case off:
        return o << "off";
    case force_correlate:
        return o << "force correlate";
    case scene:
        return o << "scene";
    case target:
        return o << "target";
    case ship:
        return o << "ship";
    default:
        return o << "ig-defined(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::sensor_control& value) -> std::ostream&
{
    o << "sensor_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tview_id: " << value.view_id;
    o << "\n\tsensor_id: " << (int)value.sensor_id;
    o << "\n\tsensor_on_off: " << value.sensor_on_off;
    o << "\n\tpolarity: " << value.polarity;
    o << "\n\tline_by_line_dropout_enable: " << value.line_by_line_dropout_enable;
    o << "\n\tautomatic_gain: " << value.automatic_gain;
    o << "\n\ttrack_white_black: " << value.track_white_black;
    o << "\n\ttrack_mode: " << value.track_mode;
    o << "\n\tresponse_type: " << value.response_type;
    o << "\n\tgain: " << value.gain;
    o << "\n\tlevel: " << value.level;
    o << "\n\tac_coupling: " << value.ac_coupling;
    o << "\n\tnoise: " << value.noise;

    return o << "\n}";
};