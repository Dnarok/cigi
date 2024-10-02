#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.31
    struct symbol_circle_definition
    {
        enum class drawing_style_t : u8
        {
            line = 0,
            fill = 1,
        };
        struct arc_t
        {
            f32 center_u = 0.f;
            f32 center_v = 0.f;
            bounded<f32, 0.f> radius = 0.f;
            bounded<f32, 0.f> inner_radius = 0.f;
            bounded<f32, 0.f, 360.f> start_angle = 0.f;
            bounded<f32, 0.f, 360.f> end_angle = 0.f;
        };

        symbol_circle_definition() = default;
        symbol_circle_definition(const symbol_circle_definition&) = default;
        symbol_circle_definition(symbol_circle_definition&&) noexcept = default;
        ~symbol_circle_definition() = default;
        auto operator =(const symbol_circle_definition& other) -> symbol_circle_definition&
        {
            symbol_id = other.symbol_id;
            drawing_style = other.drawing_style;
            stipple_pattern = other.stipple_pattern;
            line_width = other.line_width;
            stipple_pattern_length = other.stipple_pattern_length;
            arcs = other.arcs;
            packet_size = other.packet_size;

            return *this;
        };

        static auto serialize(const symbol_circle_definition& data) -> serialize_result
        {
            serialized_data out{ data.packet_size };

            out << data.packet_id
                << data.packet_size
                << data.symbol_id
                << u8(
                    (u8(data.drawing_style) << 0)
                  | (u8(data.reserved_0)    << 1)
                )
                << data.reserved_1
                << data.stipple_pattern
                << data.line_width
                << data.stipple_pattern_length;
            for (auto arc : data.arcs)
            {
                out << arc.center_u
                    << arc.center_v
                    << arc.radius
                    << arc.inner_radius
                    << arc.start_angle
                    << arc.end_angle;
            }

            out.p.base = out.data.data();
            return std::make_pair(out, serialized_data::errors::none);
        };
        static auto deserialize(serialized_data& data, symbol_circle_definition& packet) -> serialized_data::errors
        {
            symbol_circle_definition temp;

            u8 packet_id;
            data >> packet_id;
            if (packet_id != temp.packet_id)
            {
                return serialized_data::errors::mismatched_constant;
            }

            data >> temp.packet_size.value;
            // less-than, because the standard tells us to ignore bytes past our
            // expected point for backwards compatibility - too big is not an error.
            if (data.data.size() < temp.packet_size.value)
            {
                return serialized_data::errors::mismatched_constant;
            }
            // value read in is outside of our bounds for size.
            else if (!temp.packet_size.valid())
            {
                return serialized_data::errors::mismatched_constant;
            }

            data >> temp.symbol_id;

            u8 bitfield;
            data >> bitfield;
            temp.drawing_style = drawing_style_t(bitfield      & 0b0000'0001);
            temp.reserved_0    =                 bitfield >> 1 & 0b0111'1111;

            data >> (u8&)temp.reserved_1
                 >> temp.stipple_pattern
                 >> temp.line_width
                 >> temp.stipple_pattern_length;

            temp.arcs.resize((temp.packet_size.value - 16) / 24);
            for (int i = 0; i < temp.arcs.size(); ++i)
            {
                data >> temp.arcs[i].center_u
                     >> temp.arcs[i].center_v
                     >> temp.arcs[i].radius.value
                     >> temp.arcs[i].inner_radius.value
                     >> temp.arcs[i].start_angle.value
                     >> temp.arcs[i].end_angle.value;
            }

            std::swap(temp, packet);
            return serialized_data::errors::none;
        };

        constant<u8, 31> packet_id;
        bounded<u8, 16, 232> packet_size = 16;
        u16 symbol_id = 0;
        drawing_style_t drawing_style : 1 = drawing_style_t::line;
    private:
        u8 reserved_0 : 7 = 0;
        constant<u8, 0> reserved_1;
    public:
        u16 stipple_pattern = 0;
        f32 line_width = 0.f;
        f32 stipple_pattern_length = 0.f;
        std::vector<arc_t> arcs = {};

        // fails if there are already 9 arcs, the maximum allowed in 1 packet.
        auto add_arc(const arc_t& arc) -> bool
        {
            if (arcs.size() == 9)
            {
                packet_size = u8(16 + (24 * arcs.size()));
                return false;
            }

            arcs.push_back(arc);
            packet_size = u8(16 + (24 * arcs.size()));
            
            return true;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::symbol_circle_definition::drawing_style_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_circle_definition::drawing_style_t;
    case line:
        return o << "line";
    case fill:
        return o << "fill";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_circle_definition& value) -> std::ostream&
{
    o << "symbol_circle_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size.value;
    o << "\n\tsymbol_id: " << value.symbol_id;
    o << "\n\tdrawing_style: " << value.drawing_style;
    o << "\n\tstipple_pattern: " << value.stipple_pattern;
    o << "\n\tline_width: " << value.line_width;
    o << "\n\tstipple_pattern_length: " << value.stipple_pattern_length;
    o << "\n\tarcs: (" << value.arcs.size() << ')';
    for (int i = 0; i < value.arcs.size(); ++i)
    {
        const auto& arc = value.arcs[i];
        o << "\n\t  " << i << ':';
        o << "\n\t    center_u: " << arc.center_u;
        o << "\n\t    center_v: " << arc.center_v;
        o << "\n\t    radius: " << arc.radius;
        o << "\n\t    inner_radius: " << arc.inner_radius;
        o << "\n\t    start_angle: " << arc.start_angle;
        o << "\n\t    end_angle: " << arc.end_angle;
    }

    return o << "\n}";
};