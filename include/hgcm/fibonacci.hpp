/*
 * fibonacci.hpp
 *
 *  Created on: Jan 25, 2017
 *      Author: zmij
 */

#ifndef HGCM_FIBONACCI_HPP_
#define HGCM_FIBONACCI_HPP_

#include <type_traits>

namespace hgcmp {

namespace first {

/**
 * The primary metafunction template
 */
template < ::std::size_t N >
struct fibonacci {
    static constexpr ::std::size_t value =
            fibonacci<N - 2>::value + fibonacci<N - 1>::value;
    using type = fibonacci<N>;
};

//@{
/** @name Terminal specializations */
template <>
struct fibonacci<0> {
    static constexpr ::std::size_t value = 0;
    using type = fibonacci<0>;
};

template <>
struct fibonacci<1> {
    static constexpr ::std::size_t value = 1;
    using type = fibonacci<1>;
};
//@}
} /* namespace first */


namespace second {

/**
 * The primary metafunction template
 */
template < ::std::size_t N >
struct fibonacci {
    static constexpr ::std::size_t value = fibonacci<N - 2>::value +
            fibonacci<N - 1>::value;
    using type = ::std::integral_constant< ::std::size_t, value>;
};

//@{
/** @name Terminal specializations */
template <>
struct fibonacci<0> {
    static constexpr ::std::size_t value = 0;
    using type = ::std::integral_constant<::std::size_t, value>;
};

template <>
struct fibonacci<1> {
    static constexpr ::std::size_t value = 1;
    using type = ::std::integral_constant<::std::size_t, value>;
};
//@}
} /* namespace second */

inline namespace third {

/**
 * The primary metafunction template
 */
template < ::std::size_t N >
struct fibonacci :
    ::std::integral_constant<::std::size_t,
         fibonacci<N - 2>::value + fibonacci<N - 1>::value> {};

//@{
/** @name Terminal specializations */
template <>
struct fibonacci<0> : ::std::integral_constant<::std::size_t, 0> {};

template <>
struct fibonacci<1> : ::std::integral_constant<::std::size_t, 1> {};
//@}

} /* namespace third */

}  /* namespace hgcm */


#endif /* HGCM_FIBONACCI_HPP_ */
