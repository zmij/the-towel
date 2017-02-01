/*
 * iostreamable.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#ifndef HGCM_VOL1_IOSTREAMABLE_HPP_
#define HGCM_VOL1_IOSTREAMABLE_HPP_

#include <type_traits>

namespace hgcmp {

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

}  /* namespace hgcm */

#endif /* HGCM_VOL1_IOSTREAMABLE_HPP_ */
