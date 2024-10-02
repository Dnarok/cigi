#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.21
    struct alignas(std::uint64_t) view_definition
    {
        enum class mirror_mode_t : u8
        {
            none = 0,
            horizontal = 1,
            vertical = 2,
            both = 3,
        };
        enum class pixel_replication_mode_t : u8
        {
            none = 0,
            _1_by_2 = 1,
            _2_by_1 = 2,
            _2_by_2 = 3,
        };
        enum class projection_type_t : u8
        {
            perspective = 0,
            orthographic_parallel = 1,
        };
        enum class reorder_t : u8
        {
            no_reorder = 0,
            bring_to_top = 1,
        };

        constexpr view_definition() = default;
        constexpr view_definition(const view_definition&) = default;
        constexpr view_definition(view_definition&&) noexcept = default;
        constexpr ~view_definition() = default;
        constexpr auto operator =(const view_definition& other) -> view_definition&
        {
            view_id = other.view_id;
            group_id = other.group_id;
            near_enable = other.near_enable;
            far_enable = other.far_enable;
            left_enable = other.left_enable;
            right_enable = other.right_enable;
            top_enable = other.top_enable;
            bottom_enable = other.bottom_enable;
            mirror_mode = other.mirror_mode;
            pixel_replication_mode = other.pixel_replication_mode;
            projection_type = other.projection_type;
            reorder = other.reorder;
            view_type = other.view_type;
            near = other.near;
            far = other.far;
            left = other.left;
            right = other.right;
            top = other.top;
            bottom = other.bottom;

            return *this;
        };

        static auto serialize(const view_definition& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, view_definition& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 21> packet_id;
        constant<u8, 32> packet_size;
        u16 view_id = 0;
        u8 group_id = 0;
        enable_t near_enable : 1 = enable_t::disabled;
        enable_t far_enable : 1 = enable_t::disabled;
        enable_t left_enable : 1 = enable_t::disabled;
        enable_t right_enable : 1 = enable_t::disabled;
        enable_t top_enable : 1 = enable_t::disabled;
        enable_t bottom_enable : 1 = enable_t::disabled;
        mirror_mode_t mirror_mode : 2 = mirror_mode_t::none;
        pixel_replication_mode_t pixel_replication_mode : 3 = pixel_replication_mode_t::none;
        projection_type_t projection_type : 1 = projection_type_t::perspective;
        reorder_t reorder : 1 = reorder_t::no_reorder;
        u8 view_type : 3 = 0;
    private:
        constant<u8, 0> reserved_0;
    public:
        bounded<f32, 0.f> near = 0.f;
        bounded<f32, 0.f> far = 0.f;
        bounded<f32, -90.f, 90.f> left = 0.f;
        bounded<f32, -90.f, 90.f> right = 0.f;
        bounded<f32, -90.f, 90.f> top = 0.f;
        bounded<f32, -90.f, 90.f> bottom = 0.f;
    };
};

inline auto operator <<(std::ostream& o, const cigi::view_definition::mirror_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::view_definition::mirror_mode_t;
    case none:
        return o << "none";
    case horizontal:
        return o << "horizontal";
    case vertical:
        return o << "vertical";
    case both:
        return o << "horizontal and vertical";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::view_definition::projection_type_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::view_definition::projection_type_t;
    case perspective:
        return o << "perspective";
    case orthographic_parallel:
        return o << "orthographic parallel";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::view_definition::pixel_replication_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::view_definition::pixel_replication_mode_t;
    case none:
        return o << "none";
    case _1_by_2:
        return o << "1 x 2";
    case _2_by_1:
        return o << "2 x 1";
    case _2_by_2:
        return o << "2 x 2";
    default:
        return o << "ig-defined(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::view_definition::reorder_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::view_definition::reorder_t;
    case no_reorder:
        return o << "no reorder";
    case bring_to_top:
        return o << "bring to top";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

inline auto operator <<(std::ostream& o, const cigi::view_definition& value) -> std::ostream&
{
    o << "view_definition {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size:" << (int)value.packet_size;
    o << "\n\tview_id: " << value.view_id;
    o << "\n\tgroup_id: " << (int)value.group_id;
    o << "\n\tnear_enable: " << value.near_enable;
    o << "\n\tfar_enable: " << value.far_enable;
    o << "\n\tleft_enable: " << value.left_enable;
    o << "\n\tright_enable: " << value.right_enable;
    o << "\n\ttop_enable: " << value.top_enable;
    o << "\n\tbottom_enable: " << value.bottom_enable;
    o << "\n\tmirror_mode: " << value.mirror_mode;
    o << "\n\tpixel_replication_mode: " << value.pixel_replication_mode;
    o << "\n\tprojection_type: " << value.projection_type;
    o << "\n\treorder: " << value.reorder;
    o << "\n\tview_type: " << (int)value.view_type;
    o << "\n\tnear: " << value.near;
    o << "\n\tfar: " << value.far;
    o << "\n\tleft: " << value.left;
    o << "\n\tright: " << value.right;
    o << "\n\ttop: " << value.top;
    o << "\n\tbottom: " << value.bottom;

    return o << "\n}";
};