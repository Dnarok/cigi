#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.6
    struct alignas(std::uint64_t) sensor_response
    {
        enum class sensor_status_t : u8
        {
            searching_for_target = 0,
            tracking_target = 1,
            impending_breaklock = 2,
            breaklock = 3,
        };

        constexpr sensor_response() = default;
        constexpr sensor_response(const sensor_response&) = default;
        constexpr sensor_response(sensor_response&&) noexcept = default;
        constexpr ~sensor_response() = default;
        constexpr auto operator =(const sensor_response& other) -> sensor_response&
        {
            view_id = other.view_id;
            sensor_id = other.sensor_id;
            sensor_status = other.sensor_status;
            gate_x_size = other.gate_x_size;
            gate_y_size = other.gate_y_size;
            gate_x_position = other.gate_x_position;
            gate_y_position = other.gate_y_position;
            host_frame_number = other.host_frame_number;

            return *this;
        };

        static auto serialize(const sensor_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, sensor_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 106> packet_id;
        constant<u8, 24> packet_size;
        u16 view_id = 0;
        u8 sensor_id = 0;
        sensor_status_t sensor_status : 2 = sensor_status_t::searching_for_target;
    private:
        u8 reserved_0 : 6 = 0;
        constant<u16, 0> reserved_1;
    public:
        u16 gate_x_size = 0;
        u16 gate_y_size = 0;
        f32 gate_x_position = 0;
        f32 gate_y_position = 0;
        u32 host_frame_number = 0;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::sensor_response::sensor_status_t& value) -> ostream&
{
    switch (value)
    {
    using enum cigi::sensor_response::sensor_status_t;
    case searching_for_target:
        return o << "searching for target";
    case tracking_target:
        return o << "tracking target";
    case impending_breaklock:
        return o << "impending breaklock";
    case breaklock:
        return o << "breaklock";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::sensor_response& value) -> ostream&
{
    o << "sensor_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tview_id: " << value.view_id;
    o << "\n\tsensor_id: " << (int)value.sensor_id;
    o << "\n\tsensor_status: " << value.sensor_status;
    o << "\n\tgate_x_size: " << value.gate_x_size;
    o << "\n\tgate_y_size: " << value.gate_y_size;
    o << "\n\tgate_x_position: " << value.gate_x_position;
    o << "\n\tgate_y_position: " << value.gate_y_position;
    o << "\n\thost_frame_number: " << value.host_frame_number;

    return o << "\n}";
};