#pragma once

#include "general.hpp"

namespace cigi
{
    // VERSION 3.3, see CIGI ICD v3.3 § 4.1.27
    struct alignas(std::uint64_t) position_request
    {
        enum class update_mode_t : u8
        {
            one_shot = 0,
            continuous = 1,
        };
        enum class object_class_t : u8
        {
            entity = 0,
            articulated_part = 1,
            view = 2,
            view_group = 3,
            motion_tracker = 4,
        };
        enum class coordinate_system_t : u8
        {
            geodetic = 0,
            parent_entity = 1,
            submodel = 2,
        };

        constexpr position_request() = default;
        constexpr position_request(const position_request&) = default;
        constexpr position_request(position_request&&) noexcept = default;
        constexpr ~position_request() = default;
        constexpr auto operator =(const position_request& other) -> position_request&
        {
            object_id = other.object_id;
            articulated_part_id = other.articulated_part_id;
            update_mode = other.update_mode;
            object_class = other.object_class;
            coordinate_system = other.coordinate_system;

            return *this;
        };

        static auto serialize(const position_request& data) -> serialize_result
        {
            return default_serialize(data);
        };
        static auto deserialize(serialized_data& data, position_request& packet) -> serialized_data::errors
        {
            return default_deserialize(data, packet);
        };

        constant<u8, 27> packet_id;
        constant<u8, 8> packet_size;
        u16 object_id = 0;
        u8 articulated_part_id = 0;
        update_mode_t update_mode : 1 = update_mode_t::one_shot;
        object_class_t object_class : 3 = object_class_t::entity;
        coordinate_system_t coordinate_system : 2 = coordinate_system_t::geodetic;
    private:
        u8 reserved_1 : 2 = 0;
        constant<u16, 0> reserved_2;
    };
};

inline auto operator <<(std::ostream& o, const cigi::position_request::update_mode_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::position_request::update_mode_t;
    case one_shot:
        return o << "one-shot";
    case continuous:
        return o << "continuous";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::position_request::object_class_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::position_request::object_class_t;
    case entity:
        return o << "entity";
    case articulated_part:
        return o << "articulated part";
    case view:
        return o << "view";
    case view_group:
        return o << "view group";
    case motion_tracker:
        return o << "motion tracker";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::position_request::coordinate_system_t& value) -> std::ostream&
{
    switch (value)
    {
    using enum cigi::position_request::coordinate_system_t;
    case geodetic:
        return o << "geodetic";
    case parent_entity:
        return o << "parent entity";
    case submodel:
        return o << "submodel";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::position_request& value) -> std::ostream&
{
    o << "position_request {";
    o << "\n\tpacket_id: " << (int)value.packet_id;
    o << "\n\tpacket_size: " << (int)value.packet_size;
    o << "\n\tobject_id: " << value.object_id;
    o << "\n\tarticulated_part_id: " << (int)value.articulated_part_id;
    o << "\n\tupdate_mode: " << value.update_mode;
    o << "\n\tobject_class: " << value.object_class;
    o << "\n\tcoordinate_system: " << value.coordinate_system;

    return o << "\n}";
};