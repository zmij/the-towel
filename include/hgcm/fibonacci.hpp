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

template < ::std::size_t N >
struct fibonacci {
    static constexpr ::std::size_t value = fibonacci<N - 2>::value +
            fibonacci<N - 1>::value;
    using type = ::std::integral_constant< ::std::size_t, value>;
};

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

}  /* namespace hgcm */


#endif /* HGCM_FIBONACCI_HPP_ */
