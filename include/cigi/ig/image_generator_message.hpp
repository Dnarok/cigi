#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.17
    struct alignas(std::uint64_t) image_generator_message
    {
        constexpr image_generator_message() = default;
        constexpr image_generator_message(const image_generator_message&) = default;
        constexpr image_generator_message(image_generator_message&&) noexcept = default;
        constexpr ~image_generator_message() = default;
        constexpr auto operator =(const image_generator_message& other) -> image_generator_message&
        {


            return *this;
        };

        static auto serialize(const image_generator_message& data) -> serialize_result
        {
            serialized_data out{ data.packet_size };

            out << data.packet_id
                << data.packet_size
                << data.message_id;
            for (auto octet : data.octets)
            {
                out << octet;
            }

            out.p.base = out.data.data();
            return std::make_pair(out, serialized_data::errors::none);
        };
        static auto deserialize(serialized_data& data, image_generator_message& packet) -> serialized_data::errors
        {
            image_generator_message temp;

            u8 packet_id;
            data >> packet_id;
            if (packet_id != temp.packet_id)
            {
                return serialized_data::errors::mismatched_constant;
            }

            data >> temp.packet_size.value
                 >> temp.message_id;
            temp.octets.resize(temp.packet_size.value - 4);
            for (int i = 0; i < temp.octets.size(); ++i)
            {
                data >> temp.octets[i];
            }

            std::swap(temp, packet);
            return serialized_data::errors::none;
        };

        constant<u8, 117> packet_id;
        bounded<u8, 8, 104> packet_size = 8;
        u16 message_id = 0;
        std::vector<octet> octets = { 0, 0, 0, 0 };

        // see symbol_text_definition::set_text for in-depth explanation.
        auto set_message(std::string_view message) -> bool
        {
            if (message.size() > 100)
            {
                return false;
            }

            auto first_null = std::find(message.begin(), message.begin() + message.size(), 0);
            auto initial_size = std::distance(message.begin(), first_null) + 4;
            auto next_8 = initial_size + (8 - initial_size % 8);
            octets.clear();
            octets.resize(next_8 - 4, 0);
            std::copy(message.begin(), first_null, octets.begin());
            packet_size = u8(next_8);

            return true;
        };
        auto get_message() const -> std::string
        {
            return std::string{ octets.begin(), std::find(octets.begin(), octets.end(), 0) };
        };
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::image_generator_message& value) -> ostream&
{
    o << "image_generator_message {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tmessage_id: " << value.message_id;
    auto message = value.get_message();
    o << "\n\tmessage: \"" << message << "\" (" << message.size() << ')';
    o << "\n\toctets: { ";
    for (auto octet : value.octets)
    {
        o << (int)octet << ' ';
    }
    o << "} (" << value.octets.size() << ')';

    return o << "\n}";
};