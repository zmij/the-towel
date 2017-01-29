/*
 * iostreamable.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#ifndef HGCM_VOL1_IOSTREAMABLE_HPP_
#define HGCM_VOL1_IOSTREAMABLE_HPP_

#include <type_traits>

namespace hgcm {

namespace detail {
struct _io_meta_function_helper_ {
    template <typename T> _io_meta_function_helper_(T const&);
};

::std::false_type
operator << (::std::ostream const&, _io_meta_function_helper_ const&);
::std::false_type
operator >> (::std::istream const&, _io_meta_function_helper_ const&);

template <typename T>
class has_output_operator_impl {
    static ::std::false_type test(::std::false_type);
    static ::std::true_type  test(::std::ostream&);
public:
    using type = decltype(
        test( ::std::declval<::std::ostream&>() << ::std::declval<T>() ) );
};

template <typename T>
class has_input_operator_impl {
    static ::std::false_type test(::std::false_type);
    static ::std::true_type  test(::std::istream&);
public:
    using type = decltype(
        test( ::std::declval<::std::istream&>() >> ::std::declval<T&>() ) );
};

}  /* namespace detail */

template < typename T >
struct has_output_operator : detail::has_output_operator_impl<T>::type {};
template < typename T >
struct has_input_operator : detail::has_input_operator_impl<T>::type {};

}  /* namespace hgcm */

#endif /* HGCM_VOL1_IOSTREAMABLE_HPP_ */
