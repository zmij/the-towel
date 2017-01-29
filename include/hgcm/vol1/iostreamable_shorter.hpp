/*
 * iostreamable_shorter.hpp
 *
 *  Created on: 29 янв. 2017 г.
 *      Author: sergey.fedorov
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

::std::true_type
_test_for_io_stream_(::std::ostream&);
::std::true_type
 _test_for_io_stream_(::std::istream&);
::std::false_type
 _test_for_io_stream_(::std::false_type);

template < typename T >
struct has_output_operator_impl :
    decltype(detail::_test_for_io_stream_(
        ::std::declval<::std::ostream&>() << ::std::declval<T>())) {};

template < typename T >
struct has_input_operator_impl :
    decltype(detail::_test_for_io_stream_(
        ::std::declval<::std::istream&>() >> ::std::declval<T&>())) {};

}  /* namespace detail */

template < typename T >
struct has_output_operator : detail::has_output_operator_impl<T> {};
template < typename T >
struct has_input_operator : detail::has_input_operator_impl<T> {};

}  /* namespace hgcm */


#endif /* HGCM_VOL1_IOSTREAMABLE_HPP_ */
