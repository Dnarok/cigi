#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI_ICD_3_3.pdf § 4.1.1.
    struct alignas(std::uint64_t) ig_control
    {
        enum class ig_mode_t : u8
        {
            reset = 0,
            standby = reset,
            operate = 1,
            debug = 2,
        };

        constexpr ig_control() = default;
        constexpr ig_control(const ig_control&) = default;
        constexpr ig_control(ig_control&&) noexcept = default;
        constexpr ~ig_control() = default;
        constexpr auto operator =(const ig_control& other) -> ig_control&
        {
            database_number = other.database_number;
            ig_mode = other.ig_mode;
            timestamp_valid = other.timestamp_valid;
            extrapolation_interpolation_enable = other.extrapolation_interpolation_enable;
            host_frame_number = other.host_frame_number;
            timestamp = other.timestamp;
            last_ig_frame_number = other.last_ig_frame_number;

            return *this;
        };

        static auto serialize(const ig_control& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, ig_control& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 1> packet_id;
        constant<u8, 24> packet_size;
        constant<u8, 3> major_version;
        bounded<s8, 0, 127> database_number = 0;
        ig_mode_t ig_mode : 2 = ig_mode_t::reset;
        valid_t timestamp_valid : 1 = valid_t::invalid;
        enable_t extrapolation_interpolation_enable : 1 = enable_t::disabled;
        u8 minor_version : 4 = 2;
    private:
        constant<u8, 0> reserved_0;
    public:
        constant<u16, 0x8000> byte_swap_magic_number;
        u32 host_frame_number = 0;
        u32 timestamp = 0;
        u32 last_ig_frame_number = 0;
    private:
        constant<u32, 0> reserved_1;
    };
};

inline auto operator <<(std::ostream& o, const cigi::ig_control::ig_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::ig_control::ig_mode_t;
    case reset:
        return o << "reset/standby";
    case operate:
        return o << "operate";
    case debug:
        return o << "debug";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::ig_control& value) -> std::ostream&
{
    o << "ig_control {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tmajor_version: " << (int)value.major_version;
    o << "\n\tdatabase_number: " << (int)value.database_number.value;
    o << "\n\tbitfield: (" << int(value.minor_version << 4 
                      | (cigi::u8)value.extrapolation_interpolation_enable << 3
                      | (cigi::u8)value.timestamp_valid << 2
                      | (cigi::u8)value.ig_mode) << ')';
    o << "\n\t\tig_mode: " << value.ig_mode;
    o << "\n\t\ttimestamp_valid: " << value.timestamp_valid;
    o << "\n\t\textrapolation_interpolation_enable: " << value.extrapolation_interpolation_enable;
    o << "\n\t\tminor_version: " << (int)value.minor_version;
    o << "\n\tbyte_swap_magic_number: " << value.byte_swap_magic_number;
    o << "\n\thost_frame_number: " << value.host_frame_number;
    o << "\n\ttimestamp: " << value.timestamp;
    o << "\n\tlast_ig_frame_number: " << value.last_ig_frame_number;

    return o << "\n}";
};