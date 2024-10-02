#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.1
    struct alignas(std::uint64_t) start_of_frame
    {
        enum class ig_mode_t : u8
        {
            reset = 0,
            standby = reset,
            operate = 1,
            debug = 2,
            offline_maintenace = 3,
        };
        enum class earth_reference_model_t : u8
        {
            wgs_84 = 0,
            host_defined = 1,
        };

        constexpr start_of_frame() = default;
        constexpr start_of_frame(const start_of_frame&) = default;
        constexpr start_of_frame(start_of_frame&&) noexcept = default;
        constexpr ~start_of_frame() = default;
        constexpr auto operator =(const start_of_frame& other) -> start_of_frame&
        {
            database_number = other.database_number;
            ig_status_code = other.ig_status_code;
            ig_mode = other.ig_mode;
            timestamp_valid = other.timestamp_valid;
            earth_reference_model = other.earth_reference_model;
            byte_swap_magic_number = other.byte_swap_magic_number;
            ig_frame_number = other.ig_frame_number;
            timestamp = other.timestamp;
            last_host_frame_number = other.last_host_frame_number;

            return *this;
        };

        static auto serialize(const start_of_frame& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, start_of_frame& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 101> packet_id;
        constant<u8, 24> packet_size;
        constant<u8, 3> major_version;
        s8 database_number = 1;
        u8 ig_status_code = 0;
        ig_mode_t ig_mode : 2 = ig_mode_t::reset;
        valid_t timestamp_valid : 1 = valid_t::invalid;
        earth_reference_model_t earth_reference_model : 1 = earth_reference_model_t::wgs_84;
        u8 minor_version : 4 = 2;
        u16 byte_swap_magic_number = 0x8000;
        u32 ig_frame_number = 0;
        u32 timestamp = 0;
        u32 last_host_frame_number = 0;
    private:
        constant<u32, 0> reserved_0;
    };
};

inline auto operator <<(std::ostream& o, const cigi::start_of_frame::ig_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::start_of_frame::ig_mode_t;
    case reset:
        return o << "reset/standby";
    case operate:
        return o << "operate";
    case debug:
        return o << "debug";
    case offline_maintenace:
        return o << "offline maintenance";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::start_of_frame::earth_reference_model_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::start_of_frame::earth_reference_model_t;
    case wgs_84:
        return o << "WGS 84";
    case host_defined:
        return o << "host-defined";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::start_of_frame& value) -> ostream&
{
    o << "start_of_frame {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tmajor_version: " << (int)value.major_version;
    o << "\n\tdatabase_number: " << (int)value.database_number;
    o << "\n\tig_status_code: " << (int)value.ig_status_code;
    o << "\n\tig_mode: " << value.ig_mode;
    o << "\n\ttimestamp_valid: " << value.timestamp_valid;
    o << "\n\tearth_reference_model: " << value.earth_reference_model;
    o << "\n\tminor_version: " << (int)value.minor_version;
    o << "\n\tbyte_swap_magic_number: " << value.byte_swap_magic_number;
    o << "\n\tig_frame_number: " << value.ig_frame_number;
    o << "\n\ttimestamp: " << value.timestamp;
    o << "\n\tlast_host_frame_number: " << value.last_host_frame_number;

    return o << "\n}";
};