/*
 * has_name.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: zmij
 */

#ifndef HGCMP_VOL1_HAS_NAME_HPP_
#define HGCMP_VOL1_HAS_NAME_HPP_

#include <type_traits>

namespace hgcmp {

template < typename T >
class has_name {
    template < typename U = T >
    static ::std::true_type test(decltype(U::name)*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
    static constexpr bool value = type::value;
};

}  /* namespace hgcmp */



#endif /* HGCMP_VOL1_HAS_NAME_HPP_ */
