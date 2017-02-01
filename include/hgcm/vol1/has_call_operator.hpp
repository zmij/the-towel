/*
 * has_call_operator.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#ifndef HGCM_HAS_CALL_OPERATOR_HPP_
#define HGCM_HAS_CALL_OPERATOR_HPP_

#include <type_traits>

namespace hgcmp {

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

}  /* namespace hgcm */

#define MAKE_CHECK_EXPRESSION(name, expression) \
template < typename T  > \
class name { \
    template < typename U = T> \
    static ::std::true_type  test( decltype( expression, void() )* ); \
    static ::std::false_type test(...); \
public: \
    using type = decltype(test(nullptr)); \
};
#endif /* HGCM_HAS_CALL_OPERATOR_HPP_ */
