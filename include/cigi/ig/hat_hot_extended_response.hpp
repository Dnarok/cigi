#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.2.3
    struct hat_hot_extended_response
    {
        constexpr hat_hot_extended_response() = default;
        constexpr hat_hot_extended_response(const hat_hot_extended_response&) = default;
        constexpr hat_hot_extended_response(hat_hot_extended_response&&) noexcept = default;
        constexpr ~hat_hot_extended_response() = default;
        constexpr auto operator =(const hat_hot_extended_response& other) -> hat_hot_extended_response&
        {
            hat_hot_id = other.hat_hot_id;
            valid = other.valid;
            host_frame_number_lsn = other.host_frame_number_lsn;
            hat = other.hat;
            hot = other.hot;
            material_code = other.material_code;
            normal_vector_azimuth = other.normal_vector_azimuth;
            normal_vector_elevation = other.normal_vector_elevation;

            return *this;
        };

        static auto serialize(const hat_hot_extended_response& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, hat_hot_extended_response& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 103> packet_id;
        constant<u8, 40> packet_size;
        u16 hat_hot_id = 0;
        valid_t valid : 1 = valid_t::invalid;
    private:
        u8 reserved_0 : 3 = 0;
    public:
        u8 host_frame_number_lsn : 4 = 0;
    private:
        constant<u8, 0> reserved_1;
        constant<u16, 0> reserved_2;
    public:
        f64 hat = 0;
        f64 hot = 0;
        u32 material_code = 0;
        bounded<f32, -180.f, 180.f> normal_vector_azimuth = 0;
        bounded<f32, -90.f, 90.f> normal_vector_elevation = 0;
    private:
        constant<u32, 0> reserved_3;
    };
};

template <typename ostream>
constexpr auto operator <<(ostream& o, const cigi::hat_hot_extended_response& value) -> ostream&
{
    o << "hat_hot_extended_response {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\that_hot_id: " << value.hat_hot_id;
    o << "\n\tvalid: " << value.valid;
    o << "\n\thost_frame_number_lsn: " << (int)value.host_frame_number_lsn;
    o << "\n\that: " << value.hat;
    o << "\n\thot: " << value.hot;
    o << "\n\tmaterial_code: " << value.material_code;
    o << "\n\tnormal_vector_azimuth: " << value.normal_vector_azimuth;
    o << "\n\tnormal_vector_elevation: " << value.normal_vector_elevation;

    return o << "\n}";
};

/*
hat_hot_id
valid
host_frame_number_lsn
hat
hot
material_code
normal_vector_azimuth
normal_vector_elevation
*/