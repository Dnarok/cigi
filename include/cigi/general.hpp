#pragma once

#include <cstdint>
#include <concepts>
#include <limits>
#include <vector>
#include <ostream>

namespace cigi
{
    using octet = char;
    using u8 = std::uint8_t;
    using s8 = std::int8_t;
    using u16 = std::uint16_t;
    using s16 = std::int16_t;
    using u32 = std::uint32_t;
    using s32 = std::int32_t;
    using u64 = std::uint64_t;
    using s64 = std::int64_t;
    using f32 = float;
    using f64 = double;

    enum class enable_t : u8
    {
        disabled = 0,
        enabled = 1,
    };
    enum class valid_t : u8
    {
        invalid = 0,
        valid = 1,
    };
    enum class active_t : u8
    {
        inactive = 0,
        active = 1,
        destroyed = 2,
    };
    enum class merge_t : u8
    {
        use_last = 0,
        merge = 1,
    };
    enum class scope_t : u8
    {
        global = 0,
        regional = 1,
        entity = 2,
    };
    enum class coordinate_system_t : u8
    {
        geodetic = 0,
        entity = 1,
    };
    enum class request_type_t : u8
    {
        basic = 0,
        extended = 1,
    };
    enum class inherit_t : u8
    {
        not_inherited = 0,
        inherited = 1,
    };
    enum class attach_t : u8
    {
        detach = 0,
        attach = 1,
    };
    enum class collision_t : u8
    {
        non_entity = 0,
        entity = 1,
    };

    template <typename T>
    concept arithmetic = std::integral<T> || std::floating_point<T>;

    template <arithmetic T, T lower, T upper = std::numeric_limits<T>::max()>
    requires (lower < upper)
    struct bounded
    {
        constexpr bounded() = default;
        constexpr bounded(const bounded&) = default;
        constexpr bounded(bounded&&) noexcept = default;
        constexpr auto operator =(const bounded&) -> bounded& = default;
        constexpr auto operator <=>(const bounded&) const = default;

        constexpr bounded(T value) :
            value{ value < lower ? lower : (value > upper ? upper : value) }
        {};
        constexpr auto operator =(T value) -> bounded&
        {
            this->value = value < lower ? lower : (value > upper ? upper : value);
            return *this;
        };
        constexpr operator T() const
        {
            return value;
        };

        constexpr auto valid() const noexcept -> bool
        {
            return value >= lower && value <= upper;
        };

        T value;
    };

    // analogous to std::integral_constant, but it also maintains its constant
    // value in memory.
    template <typename T, T v>
    struct constant
    {
        static constexpr T value = v;
        using value_type = T;
        using type = constant;
        constexpr operator value_type() const noexcept
        {
            return value;
        };
        constexpr auto operator ()() const noexcept -> value_type
        {
            return value;
        };

        constexpr constant() = default;
        constexpr constant(const constant&) = default;
        constexpr constant(constant&&) noexcept = default;
        constexpr auto operator <=>(const constant&) const = default;

    private:
        value_type _value = value;
    };

    template <typename T>
    struct is_constant : std::false_type
    {};
    template <typename T, T v>
    struct is_constant<constant<T, v>> : std::true_type
    {};
    template <typename T>
    constexpr inline bool is_constant_v = is_constant<T>::value;

    struct serialized_data
    {
        // flags
        enum class errors
        {
            none = 0,

            // only applies to default_serialize and default_deserialize.
            non_constant_packet_size    = 1 << 0,
            // mismatched packet id, packet size, or major version.
            mismatched_constant         = 1 << 1,
        };

        union pointer
        {
            std::byte* base = nullptr;
            octet* octet;
            u8* u8;
            s8* s8;
            u16* u16;
            s16* s16;
            u32* u32;
            s32* s32;
            u64* u64;
            s64* s64;
            f32* f32;
            f64* f64;
        };

        serialized_data() :
            data{},
            p{ data.data() }
        {};
        serialized_data(const serialized_data& other) :
            data{ other.data },
            p{ data.data() }
        {};
        serialized_data(serialized_data&& other) noexcept :
            data{ other.data },
            p{ data.data() }
        {};
        auto operator =(const serialized_data& other) -> serialized_data&
        {
            data = other.data;
            p.base = data.data();
            return *this;
        };
        auto operator =(serialized_data&& other) noexcept -> serialized_data&
        {
            data = other.data;
            p.base = data.data();
            return *this;
        };
        
        template <u8 L, u8 H>
        serialized_data(bounded<u8, L, H> size) :
            data{ size, std::byte{} },
            p{ data.data() }
        {};
        template <u8 sz>
        serialized_data(constant<u8, sz> size) :
            data{ size, std::byte{} },
            p{ data.data() }
        {};
        serialized_data(u8 size) :
            data{ size, std::byte{} },
            p{ data.data() }
        {};
        explicit serialized_data(const std::byte* bytes, std::size_t count) :
            data{ bytes, bytes + count },
            p{ data.data() }
        {};
        explicit serialized_data(const std::vector<std::byte>& data) :
            data{ data },
            p{ this->data.data() }
        {};

        auto packet_id() const -> u8
        {
            if (!data.empty())
            {
                return u8(data[0]);
            }
            else
            {
                return 0;
            }
        };
        auto packet_size() const -> u8
        {
            if (!data.empty())
            {
                return u8(data[1]);
            }
            else
            {
                return 0;
            }
        };

        auto operator <<(const octet& value) -> serialized_data&
        {
            *p.octet++ = value;
            return *this;
        };
        auto operator <<(const u8& value) -> serialized_data&
        {
            *p.u8++ = value;
            return *this;
        };
        auto operator <<(const s8& value) -> serialized_data&
        {
            *p.s8++ = value;
            return *this;
        };
        auto operator <<(const u16& value) -> serialized_data&
        {
            *p.u16++ = value;
            return *this;
        };
        auto operator <<(const s16& value) -> serialized_data&
        {
            *p.s16++ = value;
            return *this;
        };
        auto operator <<(const u32& value) -> serialized_data&
        {
            *p.u32++ = value;
            return *this;
        };
        auto operator <<(const s32& value) -> serialized_data&
        {
            *p.s32++ = value;
            return *this;
        };
        auto operator <<(const u64& value) -> serialized_data&
        {
            *p.u64++ = value;
            return *this;
        };
        auto operator <<(const s64& value) -> serialized_data&
        {
            *p.s64++ = value;
            return *this;
        };
        auto operator <<(const f32& value) -> serialized_data&
        {
            *p.f32++ = value;
            return *this;
        };
        auto operator <<(const f64& value) -> serialized_data&
        {
            *p.f64++ = value;
            return *this;
        };

        auto operator >>(octet& value) -> serialized_data&
        {
            value = *p.octet++;
            return *this;
        };
        auto operator >>(u8& value) -> serialized_data&
        {
            value = *p.u8++;
            return *this;
        };
        auto operator >>(s8& value) -> serialized_data&
        {
            value = *p.s8++;
            return *this;
        };
        auto operator >>(u16& value) -> serialized_data&
        {
            value = *p.u16++;
            return *this;
        };
        auto operator >>(s16& value) -> serialized_data&
        {
            value = *p.s16++;
            return *this;
        };
        auto operator >>(u32& value) -> serialized_data&
        {
            value = *p.u32++;
            return *this;
        };
        auto operator >>(s32& value) -> serialized_data&
        {
            value = *p.s32++;
            return *this;
        }; 
        auto operator >>(u64& value) -> serialized_data&
        {
            value = *p.u64++;
            return *this;
        };
        auto operator >>(s64& value) -> serialized_data&
        {
            value = *p.s64++;
            return *this;
        };
        auto operator >>(f32& value) -> serialized_data&
        {
            value = *p.f32++;
            return *this;
        };
        auto operator >>(f64& value) -> serialized_data&
        {
            value = *p.f64++;
            return *this;
        };

        [[nodiscard]]
        auto size() const noexcept -> std::size_t
        {
            return data.size();
        };
        [[nodiscard]]
        auto start_pointer() const noexcept -> const std::byte*
        {
            return data.data();
        };
        [[nodiscard]]
        auto start_pointer() noexcept -> std::byte*
        {
            return data.data();
        };

        std::vector<std::byte> data;
        pointer p;
    };

    using serialize_result = std::pair<serialized_data, serialized_data::errors>;

    template <typename T>
    concept cigi_packet = requires (T t)
    {
        { T::serialize(t) } -> std::same_as<serialize_result>;
        { T::deserialize(std::declval<serialized_data&>(), t) } -> std::same_as<serialized_data::errors>;
        requires is_constant_v<decltype(T::packet_id)>;
        requires std::same_as<u8, typename decltype(T::packet_id)::value_type>;
        requires std::convertible_to<decltype(T::packet_size), u8>;
        requires alignof(T) == alignof(std::uint64_t);
    };

    template <cigi_packet T>
    requires requires (T t)
    {
        requires is_constant_v<decltype(T::packet_size)>;
        requires sizeof(T) == t.packet_size;
    }
    [[nodiscard]]
    auto default_serialize(const T& data) -> serialize_result
    {
        if (sizeof(T) != data.packet_size)
        {
            return std::make_pair(serialized_data{ data.packet_size }, serialized_data::errors::non_constant_packet_size);
        }

        serialized_data out{ data.packet_size };
        std::copy((std::byte*)(&data), (std::byte*)(&data) + u8(data.packet_size), out.data.begin());
        return std::make_pair(out, serialized_data::errors{});
    };
    template <cigi_packet T>
    requires requires (T t)
    {
        requires is_constant_v<decltype(T::packet_size)>;
        requires sizeof(T) == t.packet_size;
    }
    auto default_deserialize(serialized_data& data, T& packet) -> serialized_data::errors
    {
        std::copy(data.data.begin(), data.data.end(), (std::byte*)(&packet));
        return serialized_data::errors::none;
    };
};

inline auto operator <<(std::ostream& o, const cigi::enable_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::enable_t;
    case disabled:
        return o << "disabled";
    case enabled:
        return o << "enabled";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::valid_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::valid_t;
    case invalid:
        return o << "invalid";
    case valid:
        return o << "valid";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::active_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::active_t;
    case inactive:
        return o << "inactive";
    case active:
        return o << "active";
    case destroyed:
        return o << "destroyed";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::merge_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::merge_t;
    case use_last:
        return o << "use last";
    case merge:
        return o << "merge";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::scope_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::scope_t;
    case global:
        return o << "global";
    case regional:
        return o << "regional";
    case entity:
        return o << "entity";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::coordinate_system_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::coordinate_system_t;
    case geodetic:
        return o << "geodetic";
    case entity:
        return o << "entity";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::request_type_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::request_type_t;
    case basic:
        return o << "basic";
    case extended:
        return o << "extended";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::inherit_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::inherit_t;
    case not_inherited:
        return o << "not inherited";
    case inherited:
        return o << "inherited";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::attach_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::attach_t;
    case detach:
        return o << "detach";
    case attach:
        return o << "attach";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};
inline auto operator <<(std::ostream& o, const cigi::collision_t& value) -> std::ostream&
{
    switch (value)
    {
        using enum cigi::collision_t;
    case non_entity:
        return o << "non-entity";
    case entity:
        return o << "entity";
    default:
        return o << "unknown(" << int(value) << ')';
    }
};

template <typename T, T lower, T upper>
auto operator <<(std::ostream& o, const cigi::bounded<T, lower, upper>& value) -> std::ostream&
{
    return o << value.value;
};

template <typename T, T v>
auto operator <<(std::ostream& o, const cigi::constant<T, v>& value) -> std::ostream&
{
    return o << value.value;
};