/*
 * iostreamable.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#ifndef HGCM_IOSTREAMABLE_HPP_
#define HGCM_IOSTREAMABLE_HPP_

#include <type_traits>

namespace hgcm {

namespace detail {
struct __io_meta_function_helper {
    template <typename T> __io_meta_function_helper(T const&);
};

::std::false_type
operator << (::std::ostream const&, __io_meta_function_helper const&);
::std::false_type
operator >> (::std::istream const&, __io_meta_function_helper const&);

template <typename T>
struct has_input_operator_impl {
private:
    static ::std::false_type test(::std::false_type);
    static ::std::true_type test(::std::istream&);

    static ::std::istream& is;
    static T& val;
public:
    using type = typename ::std::is_same<
            decltype( test( is >> val ) ), ::std::true_type >::type;
};

template <typename T>
struct has_output_operator_impl {
private:
    static ::std::false_type test(std::false_type);
    static ::std::true_type test(std::ostream&);

    static ::std::ostream& os;
    static T const& val;
public:
    using type = typename ::std::is_same<
            decltype( test( os << val ) ), ::std::true_type >::type;
};
}  /* namespace detail */

template < typename T >
struct has_input_operator : detail::has_input_operator_impl<T>::type {};
template < typename T >
struct has_output_operator : detail::has_output_operator_impl<T>::type {};

}  /* namespace hgcm */

#endif /* HGCM_IOSTREAMABLE_HPP_ */
