/*
 * iostreamable_shorter.hpp
 *
 *  Created on: 29 янв. 2017 г.
 *      Author: sergey.fedorov
 */

#ifndef HGCM_VOL1_IOSTREAMABLE_HPP_
#define HGCM_VOL1_IOSTREAMABLE_HPP_

#include <type_traits>
#include <iosfwd>

namespace hgcmp {

namespace detail {
template < typename T >
class has_output_operator_impl {
    template < typename U >
    using helper = decltype( ::std::declval<::std::ostream&>() << ::std::declval<U>(), void() );

    template < typename U = T>
    static ::std::true_type  test(helper<U>*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
};

template < typename T >
class has_input_operator_impl {
    template < typename U >
    using helper = decltype( ::std::declval<::std::istream&>() >> ::std::declval<U&>(), void() );

    template < typename U = T>
    static ::std::true_type  test(helper<U>*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
};
}  /* namespace detail */

template < typename T >
struct has_output_operator : detail::has_output_operator_impl<T>::type {};
template < typename T >
struct has_input_operator : detail::has_input_operator_impl<T>::type {};

}  /* namespace hgcm */


#endif /* HGCM_VOL1_IOSTREAMABLE_HPP_ */
