#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.32
    struct symbol_line_definition
    {
        enum class primitive_type_t
        {
            point = 0,
            line = 1,
            line_strip = 2,
            line_loop = 3,
            triangle = 4,
            triangle_strip = 5,
            triangle_fan = 6,
        };
        struct vertex_t
        {
            f32 u = 0.f;
            f32 v = 0.f;
        };

        constexpr symbol_line_definition() = default;
        constexpr symbol_line_definition(const symbol_line_definition&) = default;
        constexpr symbol_line_definition(symbol_line_definition&&) noexcept = default;
        constexpr ~symbol_line_definition() = default;
        constexpr auto operator =(const symbol_line_definition& other) -> symbol_line_definition&
        {
            symbol_id = other.symbol_id;
            primitive_type = other.primitive_type;
            stipple_pattern = other.stipple_pattern;
            line_width = other.line_width;
            stipple_pattern_length = other.stipple_pattern_length;
            vertices = other.vertices;
            packet_size = other.packet_size;

            return *this;
        };

        static auto serialize(const symbol_line_definition& data) -> serialize_result
        {
            serialized_data out{ data.packet_size };

            out << data.packet_id
                << data.packet_size
                << data.symbol_id
                << u8(
                    (u8(data.primitive_type) << 0)
                  | (u8(data.reserved_0)     << 4)
                )
                << data.reserved_1
                << data.stipple_pattern
                << data.line_width
                << data.stipple_pattern_length;
            for (auto vertex : data.vertices)
            {
                out << vertex.u
                    << vertex.v;
            }

            out.p.base = out.data.data();
            return std::make_pair(out, serialized_data::errors::none);
        };
        static auto deserialize(serialized_data& data, symbol_line_definition& packet) -> serialized_data::errors
        {
            symbol_line_definition temp;

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
            temp.primitive_type = primitive_type_t(bitfield      & 0b0000'1111);
            temp.reserved_0     =                  bitfield >> 4 & 0b0000'1111;

            data >> (u8&)temp.reserved_1
                 >> temp.stipple_pattern
                 >> temp.line_width
                 >> temp.stipple_pattern_length;

            temp.vertices.resize((temp.packet_size.value - 16) / 8);
            for (int i = 0; i < temp.vertices.size(); ++i)
            {
                data >> temp.vertices[i].u
                     >> temp.vertices[i].v;
            }

            std::swap(temp, packet);
            return serialized_data::errors::none;
        };

        constant<u8, 32> packet_id;
        bounded<u8, 16, 248> packet_size = 16;
        u16 symbol_id = 0;
        primitive_type_t primitive_type : 4 = primitive_type_t::point;
    private:
        u8 reserved_0 : 4 = 0;
        constant<u8, 0> reserved_1;
    public:
        u16 stipple_pattern = 0;
        f32 line_width = 0;
        f32 stipple_pattern_length = 0;
        std::vector<vertex_t> vertices = {};
        
        // fails if there are already 29 vertices, the maximum allowed in 1 packet.
        auto add_vertex(const vertex_t& vertex) -> bool
        {
            if (vertices.size() == 29)
            {
                packet_size = u8(16 + (8 * vertices.size()));
                return false;
            }

            vertices.push_back(vertex);
            packet_size = u8(16 + (8 * vertices.size()));
            
            return true;
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::symbol_line_definition::primitive_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_line_definition::primitive_type_t;
    case point:
        return o << "point";
    case line:
        return o << "line";
    case line_strip:
        return o << "line strip";
    case line_loop:
        return o << "line loop";
    case triangle:
        return o << "triangle";
    case triangle_strip:
        return o << "triangle strip";
    case triangle_fan:
        return o << "triangle fan";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_line_definition& value) -> std::ostream&
{
    o << "symbol_line_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size.value;
    o << "\n\tsymbol_id: " << value.symbol_id;
    o << "\n\tprimitive_type: " << value.primitive_type;
    o << "\n\tstipple_pattern: " << value.stipple_pattern;
    o << "\n\tline_width: " << value.line_width;
    o << "\n\tstipple_pattern_length: " << value.stipple_pattern_length;
    o << "\n\tvertices: (" << value.vertices.size() << ')';
    for (int i = 0; i < value.vertices.size(); ++i)
    {
        const auto& vertex = value.vertices[i];
        o << "\n\t  " << i << ':';
        o << "\n\t    vertex_u: " << vertex.u;
        o << "\n\t    vertex_v: " << vertex.v;
    }

    return o << "\n}";
};