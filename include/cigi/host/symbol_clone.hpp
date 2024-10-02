#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.33
    struct alignas(std::uint64_t) symbol_clone
    {
        enum class source_type_t : u8
        {
            symbol = 0,
            symbol_template = 1,
        };

        constexpr symbol_clone() = default;
        constexpr symbol_clone(const symbol_clone&) = default;
        constexpr symbol_clone(symbol_clone&&) noexcept = default;
        constexpr ~symbol_clone() = default;
        constexpr auto operator =(const symbol_clone& other) -> symbol_clone&
        {
            symbol_id = other.symbol_id;
            source_type = other.source_type;
            source_id = other.source_id;

            return *this;
        };

        static auto serialize(const symbol_clone& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, symbol_clone& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 33> packet_id;
        constant<u8, 8> packet_size;
        u16 symbol_id = 0;
        source_type_t source_type : 1 = source_type_t::symbol;
    private:
        u8 reserved_0 : 7 = 0;
        constant<u8, 0> reserved_1;
    public:
        u16 source_id = 0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::symbol_clone::source_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::symbol_clone::source_type_t;
    case symbol:
        return o << "symbol";
    case symbol_template:
        return o << "symbol template";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::symbol_clone& value) -> std::ostream&
{
    o << "symbol_clone {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tsymbol_id: " << value.symbol_id;
    o << "\n\tsource_type: " << value.source_type;
    o << "\n\tsource_id: " << value.source_id;

    return o << "\n}";
};