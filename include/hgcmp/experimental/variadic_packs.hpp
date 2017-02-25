/*
 * variadic_packs.hpp
 *
 *  Created on: Jan 27, 2017
 *      Author: zmij
 */

#ifndef HGCMP_EXPERIMENTAL_VARIADIC_PACKS_HPP_
#define HGCMP_EXPERIMENTAL_VARIADIC_PACKS_HPP_

#include <type_traits>
#include <utility>
#include <tuple>

namespace hgcmp {
namespace experimental {

template < typename ... T >
struct type_tuple {};

//@{
/** @name Metafunctions for determining variadic pack length */
template < typename ... T >
struct pack_length {
    using type = ::std::integral_constant<::std::size_t, sizeof ... (T)>;
};

template <>
struct pack_length<> {
    using type = ::std::integral_constant<::std::size_t, 0>;
};

template < typename T >
struct pack_length<T> {
    using type = ::std::integral_constant<::std::size_t, 1>;
};

template < typename ... T >
struct pack_length<type_tuple<T...>> {
    using type = ::std::integral_constant<::std::size_t, sizeof ... (T)>;
};

template < typename T, T... Ints >
struct pack_length<::std::integer_sequence<T, Ints...>> {
    using type = ::std::integral_constant<::std::size_t, sizeof ... (Ints)>;
};

template < typename ... T >
struct pack_length<::std::tuple<T...>> {
    using type = ::std::integral_constant<::std::size_t, sizeof ... (T)>;
};
//@}

//@{
/** @name Convert integer_sequence to type_tuple and back */
template < typename T >
struct to_type_tuple;

template < typename T, T ... Ints >
struct to_type_tuple<::std::integer_sequence<T, Ints...>> {
    using type = type_tuple< ::std::integral_constant<T, Ints>... >;
};

template < typename T >
struct to_integer_sequence;

template < typename T, T... Ints >
struct to_integer_sequence<type_tuple< ::std::integral_constant<T, Ints>... >> {
    using type = ::std::integer_sequence<T, Ints...>;
};
//@}

//@{
/** @name Joining sequences */
template < typename T, typename U >
struct merge;
template < typename ... T, typename U >
struct merge< type_tuple<T...>, U > {
    using type = type_tuple<T..., U>;
};
template < typename U, typename ... T >
struct merge< U, type_tuple<T...> > {
    using type = type_tuple<U, T...>;
};

template < typename ... T, typename ... U >
struct merge< type_tuple<T...>, type_tuple<U...> > {
    using type = type_tuple<T..., U...>;
};

template < typename T, T Int, T ... Ints >
struct merge< ::std::integral_constant<T, Int>, ::std::integer_sequence< T, Ints... > > {
    using type = ::std::integer_sequence<T, Int, Ints...>;
};

template < typename T, T ... Ints, T Int >
struct merge< ::std::integer_sequence< T, Ints... >, ::std::integral_constant<T, Int> > {
    using type = ::std::integer_sequence<T, Ints..., Int>;
};

template < typename T, T... Rhs, T... Lhs >
struct merge< ::std::integer_sequence< T, Rhs... >, ::std::integer_sequence<T, Lhs...> > {
    using type = ::std::integer_sequence<T, Rhs..., Lhs...>;
};
//@}

//@{
/** @name Reversing packs */
template < typename ... T >
struct reverse : reverse< type_tuple<T...> >{};

template < typename T, typename ... U >
struct reverse< type_tuple<T, U...> > {
    using type = typename merge< typename reverse<U...>::type, T >::type;
};

template <>
struct reverse< type_tuple<> > {
    using type = type_tuple<>;
};

template < typename T, T Int, T ... Ints >
struct reverse< ::std::integer_sequence< T, Int, Ints... > > {
    using type = typename merge<
            typename reverse<::std::integer_sequence<T, Ints...>>::type,
             ::std::integral_constant<T, Int> >::type;
};

template <typename T>
struct reverse< ::std::integer_sequence<T> > {
    using type = ::std::integer_sequence<T>;
};

template < typename T, T ... Ints >
struct reverse_c {
    using type = typename reverse< ::std::integer_sequence<T, Ints...> >::type;
};

//@}

}  /* namespace experimental */
}  /* namespace hgcm */



#endif /* HGCMP_EXPERIMENTAL_VARIADIC_PACKS_HPP_ */
