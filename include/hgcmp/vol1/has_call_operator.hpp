/*
 * has_call_operator.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#ifndef HGCM_HAS_CALL_OPERATOR_HPP_
#define HGCM_HAS_CALL_OPERATOR_HPP_

#include <hgcmp/vol1/void_t.hpp>
#include <type_traits>

namespace hgcmp {
inline namespace first {
template< typename T >
class has_call_operator {
    template < typename U = T>
    static ::std::true_type  test( decltype( &U::operator() ) );
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
};

template < typename T, typename ... Args >
class is_callable {
    template < typename U = T>
    static ::std::true_type  test(
            decltype( ::std::declval<U>()(::std::declval<Args>()...), void() )* );
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
};
}  /* namespace first */
namespace second {

template < typename T, typename = void_t<> >
struct has_call_operator : ::std::false_type {};

template < typename T >
struct has_call_operator<T, void_t< decltype( &T::operator() ) >> : ::std::true_type {};

}  /* namespace second */
}  /* namespace hgcm */

#endif /* HGCM_HAS_CALL_OPERATOR_HPP_ */
