/*
 * has_call_operator.hpp
 *
 *  Created on: 26 янв. 2017 г.
 *      Author: sergey.fedorov
 */

#ifndef HGCM_HAS_CALL_OPERATOR_HPP_
#define HGCM_HAS_CALL_OPERATOR_HPP_

#include <type_traits>

namespace hgcm {

namespace detail {

template< typename T >
class has_call_operator_impl {
    template < typename U >
    static ::std::true_type
    test( decltype( &U::operator() )* );

    template < typename U >
    static ::std::false_type
    test(...);
public:
    using type = decltype(test<T>(nullptr));
};

}  /* namespace detail */

template < typename T >
struct has_call_operator : detail::has_call_operator_impl<T>::type {};

}  /* namespace hgcm */


#endif /* HGCM_HAS_CALL_OPERATOR_HPP_ */
