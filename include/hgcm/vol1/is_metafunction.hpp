/*
 * is_metafunction.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: zmij
 */

#ifndef HGCM_VOL1_IS_METAFUNCTION_HPP_
#define HGCM_VOL1_IS_METAFUNCTION_HPP_

#include <type_traits>

namespace hgcmp {

template < typename T >
class is_metafunction {
    template < typename U = T >
    static ::std::true_type test(typename U::type*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
    static constexpr bool value = type::value;
};

}  /* namespace hgcm */



#endif /* HGCM_VOL1_IS_METAFUNCTION_HPP_ */
