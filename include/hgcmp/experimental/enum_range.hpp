/*
 * enum_range.hpp
 *
 *  Created on: Mar 5, 2017
 *      Author: zmij
 */

#ifndef HGCMP_EXPERIMENTAL_ENUM_RANGE_HPP_
#define HGCMP_EXPERIMENTAL_ENUM_RANGE_HPP_

#include <type_traits>

namespace hgcmp {

namespace detail {

template < typename T, T ... Enumerators >
struct enumerators  {
    static_assert( ::std::is_enum<T>::value,
            "Cannot instantiate enumerators for a non-enum" );

    using value_type    = T;
    using iterator      = T const*;
    using size          = ::std::integral_constant<
                            ::std::size_t, sizeof ... (Enumerators)>;
    static constexpr const value_type   values[] { Enumerators... };
    static constexpr const iterator     begin   = values;
    static constexpr const iterator     end     = values + size::value;

    static constexpr iterator
    position(value_type v)
    {
        auto p = begin;
        for (; p != end; ++p) {
            if (*p == v)
                break;
        }
        return p;
    }
};

template < typename T, T ... Enumerators >
constexpr const T enumerators<T, Enumerators...>::values[];

} /* namespace detail */


template < typename T >
struct enum_traits_base {
    using value_type    = T;
    using iterator      = T const*;
};

template < typename T >
struct enum_traits : enum_traits_base<T> {
    using value_type    = typename enum_traits_base<T>::value_type;
    using iterator      = typename enum_traits_base<T>::iterator;
    using enumerators   = detail::enumerators<T>;
};

namespace detail {

struct enum_begin_type {};
struct enum_end_type   {};

template < typename T, bool >
struct enum_value_range_impl {
    using traits_type   = enum_traits<T>;
    using value_type    = typename traits_type::value_type;
    using iterator      = typename traits_type::iterator;
    using enumerators   = typename traits_type::enumerators;

    constexpr
    enum_value_range_impl()
        : enum_value_range_impl{enumerators::begin, enumerators::end} {}

    constexpr
    enum_value_range_impl(value_type first, value_type last)
        : enum_value_range_impl{
            enumerators::position(first), enumerators::position(last)} {}

    constexpr
    enum_value_range_impl(value_type first, enum_end_type)
        : enum_value_range_impl{
            enumerators::position(first), enumerators::end} {}

    constexpr
    enum_value_range_impl(enum_begin_type, value_type last)
        : enum_value_range_impl{
            enumerators::begin, enumerators::position(last)} {}

    constexpr
    enum_value_range_impl(enum_value_range_impl const&) = default;
    constexpr
    enum_value_range_impl(enum_value_range_impl&&) = default;

    constexpr ::std::size_t
    size() const
    { return end_ - begin_; }
    constexpr bool
    empty() const
    { return begin_ == end_; }

    constexpr iterator
    begin() const
    { return begin_; }
    constexpr iterator
    end() const
    { return end_; }

    constexpr value_type
    front() const
    { return *begin_; }
    constexpr value_type
    back() const
    { return *(end_ - 1); }
private:
    constexpr
    enum_value_range_impl(iterator first, iterator last)
        : begin_{first}, end_{last} {}
private:
    iterator begin_;
    iterator end_;
};

template < typename T >
struct enum_value_range_impl<T, false> {
    static_assert( ::std::is_enum<T>::value, "Cannot instantiate enum_value_range for a non-enum" );
};

} /* namespace detail */

detail::enum_begin_type const enum_begin{};
detail::enum_end_type   const enum_end{};

template < typename T >
struct enum_value_range : detail::enum_value_range_impl<T, ::std::is_enum<T>::value> {
    using base_type     = detail::enum_value_range_impl<T, ::std::is_enum<T>::value>;
    using base_type::base_type;
};

template < typename T >
constexpr enum_value_range<T>
enum_range()
{ return {}; }

template < typename T >
constexpr enum_value_range<T>
enum_range(T first, T last)
{ return { first, last }; }

template < typename T >
constexpr enum_value_range<T>
enum_range(T first, detail::enum_end_type e)
{ return { first, e }; }

template < typename T >
constexpr enum_value_range<T>
enum_range(detail::enum_begin_type b, T last)
{ return { b, last }; }

} /* namespace hgcmp */



#endif /* HGCMP_EXPERIMENTAL_ENUM_RANGE_HPP_ */
