/*
 * iostreamable.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#ifndef HGCM_VOL1_IOSTREAMABLE_HPP_
#define HGCM_VOL1_IOSTREAMABLE_HPP_

#include <type_traits>
#include <hgcm/vol1/void_t.hpp>

namespace hgcmp {

inline namespace first {
template < typename T >
class has_output_operator {
    template < typename U >
    using helper = decltype( ::std::declval<::std::ostream&>() << ::std::declval<U>(), void() );

    template < typename U = T>
    static ::std::true_type  test(helper<U>*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
};

template < typename T >
class has_input_operator {
    template < typename U >
    using helper = decltype( ::std::declval<::std::istream&>() >> ::std::declval<U&>(), void() );

    template < typename U = T>
    static ::std::true_type  test(helper<U>*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
};
}

namespace second {

template < typename T, typename = void_t<> >
struct has_output_operator : ::std::false_type {};

template < typename T >
struct has_output_operator< T,
    void_t< decltype(
        ::std::declval<::std::ostream&>() << ::std::declval<T>()) >>
             : ::std::true_type {};

template < typename T, typename = void_t<> >
struct has_input_operator : ::std::false_type {};

template < typename T >
struct has_input_operator< T,
    void_t< decltype(
        ::std::declval<::std::istream&>() >> ::std::declval<T&>()) >>
             : ::std::true_type {};

}  /* namespace second */

}  /* namespace hgcm */

#endif /* HGCM_VOL1_IOSTREAMABLE_HPP_ */
