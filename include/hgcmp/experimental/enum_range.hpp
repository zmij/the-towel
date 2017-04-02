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
namespace experimental {

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
    		iterator left = begin;
    		iterator right = end;
    		while (left != right) {
    			iterator mid = left + (right - left) / 2;
    			if (v <= *mid) {
    				right = mid;
    			} else {
    				left = mid + 1;
    			}
    		}
    		if (v == *right)
    			return right;
        return end;
    }
};

template < typename T, T ... Enumerators >
constexpr const T enumerators<T, Enumerators...>::values[];

template < typename Enum >
struct enumerators< Enum > {
	static_assert(::std::is_same< Enum, Enum >::value, "enum_traits were not defined");
};

} /* namespace detail */


template < typename T >
struct enum_traits {
    using enumerators   = detail::enumerators<T>;
};

namespace detail {

struct enum_begin {
	constexpr enum_begin() {}
};
struct enum_end   {
	constexpr enum_end()   {}
};
} /* namespace detail */

constexpr detail::enum_begin const enum_begin{};
constexpr detail::enum_end   const enum_end{};

template < typename Enum >
struct enum_value_range {
	static_assert(::std::is_enum< Enum >::value, "Cannot instantiate enum_value_range for a non-enum");
	using traits_type	= enum_traits< Enum >;
	using enumerators	= typename traits_type::enumerators;
	using value_type		= typename enumerators::value_type;
	using iterator		= typename enumerators::iterator;

	constexpr enum_value_range()
		: enum_value_range{ enumerators::begin, enumerators::end } {}
	constexpr enum_value_range(value_type begin, value_type end)
		: enum_value_range{ enumerators::position(begin), enumerators::position(end) } {}
	constexpr enum_value_range(detail::enum_begin, value_type end)
		: enum_value_range{ enumerators::begin, enumerators::position(end) } {}
	constexpr enum_value_range(value_type begin, detail::enum_end)
		: enum_value_range{ enumerators::position(begin), enumerators::end } {}
	constexpr enum_value_range(enum_value_range const&) = default;
	constexpr enum_value_range(enum_value_range&&) = default;

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
	constexpr enum_value_range(iterator b, iterator e)
		: begin_{b}, end_{e} {}
	iterator begin_;
	iterator end_;
};

template <typename Enum>
enum_value_range<Enum>
enum_range()
{ return {}; }

template <typename Enum>
enum_value_range<Enum>
enum_range(Enum begin, Enum end)
{ return { begin, end }; }

template <typename Enum>
enum_value_range<Enum>
enum_range(detail::enum_begin begin, Enum end)
{ return { begin, end }; }

template <typename Enum>
enum_value_range<Enum>
enum_range(Enum begin, detail::enum_end end)
{ return { begin, end }; }

}  // namespace experimental
} /* namespace hgcmp */



#endif /* HGCMP_EXPERIMENTAL_ENUM_RANGE_HPP_ */
