#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.30
    struct symbol_text_definition
    {
        enum class alignment_t : u8
        {
            top_left = 0,
            top_center = 1,
            top_right = 2,
            center_left = 3,
            center = 4,
            center_right = 5,
            bottom_left  = 6,
            bottom_center = 7,
            bottom_right = 8,
        };
        enum class orientation_t : u8
        {
            left_to_right = 0,
            top_to_bottom = 1,
            right_to_left = 2,
            bottom_to_top = 3,
        };
        enum class font_t : u8
        {
            ig_default = 0,
            proportional_sans_serif = 1,
            proportional_sans_serif_bold = 2,
            proportional_sans_serif_italic = 3,
            proportional_sans_serif_bold_italic = 4,
            proportional_serif = 5,
            proportional_serif_bold = 6,
            proportional_serif_italic = 7,
            proportional_serif_bold_italic = 8,
            monospace_sans_serif = 9,
            monospace_sans_serif_bold = 10,
            monospace_sans_serif_italic = 11,
            monospace_sans_serif_bold_italic = 12,
            monospace_serif = 13,
            monospace_serif_bold = 14,
            monospace_serif_italic = 15,
            monospace_serif_bold_italic = 16,
        };

        symbol_text_definition() = default;
        symbol_text_definition(const symbol_text_definition&) = default;
        symbol_text_definition(symbol_text_definition&&) noexcept = default;
        ~symbol_text_definition() = default;
        auto operator =(const symbol_text_definition& other) -> symbol_text_definition&
        {
            symbol_id = other.symbol_id;
            alignment = other.alignment;
            orientation = other.orientation;
            font_id = other.font_id;
            font_size = other.font_size;
            octets = other.octets;
            packet_size = other.packet_size;

            return *this;
        };

        static auto serialize(const symbol_text_definition& data) -> serialize_result
        {
            serialized_data out{ data.packet_size };

            out << data.packet_id
                << data.packet_size
                << data.symbol_id
                << u8(
                    (u8(data.alignment)   << 0)
                  | (u8(data.orientation) << 4)
                  | (u8(data.reserved_0)  << 6)
                )
                << cigi::u8(data.font_id)
                << data.reserved_1
                << data.font_size;
            for (auto octet : data.octets)
            {
                out << octet;
            }

            out.p.base = out.data.data();
            return std::make_pair(out, serialized_data::errors::none);
        };
        static auto deserialize(serialized_data& data, symbol_text_definition& packet) -> serialized_data::errors
        {
            symbol_text_definition temp;

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
            temp.alignment   = alignment_t  (bitfield      & 0b0000'1111);
            temp.orientation = orientation_t(bitfield >> 4 & 0b0000'0011);
            temp.reserved_0  =               bitfield >> 6 & 0b0000'0011;

            data >> (u8&)temp.font_id
                 >> (u16&)temp.reserved_1
                 >> temp.font_size;

            temp.octets.resize(temp.packet_size.value - 12);
            for (int i = 0; i < temp.octets.size(); ++i)
            {
                data >> temp.octets[i];
            }

            std::swap(temp, packet);
            return serialized_data::errors::none;
        };

        constant<u8, 30> packet_id;
        bounded<u8, 16, 248> packet_size = 16;
        u16 symbol_id = 0;
        alignment_t alignment : 4 = alignment_t::top_left;
        orientation_t orientation : 2 = orientation_t::left_to_right;
    private:
        u8 reserved_0 : 2 = 0;
    public:
        font_t font_id = font_t::ig_default;
    private:
        constant<u16, 0> reserved_1;
    public:
        f32 font_size = 0.f;
        std::vector<octet> octets = { 0, 0, 0, 0 };

        // fails if text would be cut off (text.size() > 235).
        auto set_text(std::string_view text) -> bool
        {
            if (text.size() > 235)
            {
                return false;
            }
            
            // find the first NULL character in the text, if it has one.
            // if we don't have one, we assume one-past-the-end is the first.
            auto first_null = std::find(text.begin(), text.begin() + text.size(), 0);
            // calculate the size that the packet will be once we add this text.
            auto initial_size = std::distance(text.begin(), first_null) + 12;
            // determine what multiple of 8 our size will need to be.
            auto next_8 = initial_size + (8 - initial_size % 8);
            // clear any previous content.
            octets.clear();
            // resize to the new required text size, filling with NULL.
            octets.resize(next_8 - 12, 0);
            // copy the text in.
            std::copy(text.begin(), first_null, octets.begin());
            // set the packet size to the next-highest-8.
            packet_size = u8(next_8);

            // this is done so that if some text is added that has a NULL character
            // in the middle, it will erase the amount required to abide by the 
            // standard - up to the next highest multiple of 8.

            return true;
        };
        auto get_text() const -> std::string
        {
            return std::string{ octets.begin(), std::find(octets.begin(), octets.end(), 0) };
        };
    };
};

inline auto operator <<(std::ostream& o, const cigi::symbol_text_definition::alignment_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_text_definition::alignment_t;
    case top_left:
        return o << "top left";
    case top_center:
        return o << "top center";
    case top_right:
        return o << "top right";
    case center_left:
        return o << "center left";
    case center:
        return o << "center";
    case center_right:
        return o << "center right";
    case bottom_left:
        return o << "bottom left";
    case bottom_center:
        return o << "bottom center";
    case bottom_right:
        return o << "bottom right";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_text_definition::orientation_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_text_definition::orientation_t;
    case left_to_right:
        return o << "left-to-right";
    case top_to_bottom:
        return o << "top-to-bottom";
    case right_to_left:
        return o << "right-to-left";
    case bottom_to_top:
        return o << "bottom-to-top";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_text_definition::font_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_text_definition::font_t;
    case ig_default:
        return o << "ig default"; 
    case proportional_sans_serif:
        return o << "proportional sans serif"; 
    case proportional_sans_serif_bold:
        return o << "proportional sans serif bold"; 
    case proportional_sans_serif_italic:
        return o << "proportional sans serif italic"; 
    case proportional_sans_serif_bold_italic:
        return o << "proportional sans serif bold italic"; 
    case proportional_serif:
        return o << "proportional serif"; 
    case proportional_serif_bold:
        return o << "proportional serif bold"; 
    case proportional_serif_italic:
        return o << "proportional serif italic"; 
    case proportional_serif_bold_italic:
        return o << "proportional serif bold italic"; 
    case monospace_sans_serif:
        return o << "monospace sans serif"; 
    case monospace_sans_serif_bold:
        return o << "monospace sans serif bold";
    case monospace_sans_serif_italic:
        return o << "monospace sans serif italic";
    case monospace_sans_serif_bold_italic:
        return o << "monospace sans serif bold italic";
    case monospace_serif:
        return o << "monospace serif";
    case monospace_serif_bold:
        return o << "monospace serif bold";
    case monospace_serif_italic:
        return o << "monospace serif italic";
    case monospace_serif_bold_italic:
        return o << "monospace serif bold italic";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_text_definition& value) -> std::ostream&
{
    o << "symbol_text_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size.value;
    o << "\n\tsymbol_id: " << value.symbol_id;
    o << "\n\talignment: " << value.alignment;
    o << "\n\torientation: " << value.orientation;
    o << "\n\tfont_id: " << value.font_id;
    o << "\n\tfont_size: " << value.font_size;
    auto text = value.get_text();
    o << "\n\ttext: \"" << text << "\" (" << text.size() << ')';
    o << "\n\toctets: { ";
    for (auto octet : value.octets)
    {
        o << (int)octet << ' ';
    }
    o << "} (" << value.octets.size() << ')';

    return o << "\n}";
};