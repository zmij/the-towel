/*
 * char_classification.hpp
 *
 *  Created on: Mar 6, 2017
 *      Author: zmij
 */

#ifndef HGCMP_EXPERIMENTAL_CHAR_CLASSIFICATION_HPP_
#define HGCMP_EXPERIMENTAL_CHAR_CLASSIFICATION_HPP_

#include <type_traits>
#include <utility>

namespace hgcmp {

//----------------------------------------------------------------------------
namespace detail {
template < char C, char ... Chars >
struct first_char {
    using type = ::std::integral_constant<char, C>;
};

template < char C, char ... Chars >
struct last_char : last_char< Chars ... > {};
template < char C >
struct last_char<C> {
    using type = ::std::integral_constant<char, C>;
};
} /* namespace detail */
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
template < char ... Chars >
struct char_sequence {
    using size          = ::std::integral_constant<::std::size_t, sizeof ... (Chars)>;
    using first_char    = typename detail::first_char<Chars...>::type;
    using last_char     = typename detail::last_char<Chars...>::type;
};

template <>
struct char_sequence<> {
    using size          = ::std::integral_constant<::std::size_t, 0>;
};

template < char Min, char Max >
struct char_range {
    static_assert(Min <= Max, "Minimum char must be less or equal to maximum");
    using size          = ::std::integral_constant<::std::size_t, Max - Min + 1>;
    using first_char    = ::std::integral_constant<char, Min>;
    using last_char     = ::std::integral_constant<char, Max>;
};

//----------------------------------------------------------------------------
//@{
template < typename T, char>
struct contains;

template < char F, char ... O, char C >
struct contains< char_sequence<F, O...>, C > : contains< char_sequence<O...>, C > {};

template < char ... O, char C >
struct contains< char_sequence<C, O...>, C > : ::std::true_type {};

template < char C >
struct contains< char_sequence<>, C > : ::std::false_type {};

template < char Min, char Max, char C >
struct contains< char_range<Min, Max>, C > :
    ::std::integral_constant<bool, (Min <= C && C <= Max)> {};
//@}

//----------------------------------------------------------------------------
template < typename T, char C >
struct push_back;

template < char ... Chars, char C >
struct push_back<char_sequence<Chars ...>, C> {
    using type = char_sequence<Chars..., C>;
};

//----------------------------------------------------------------------------
template < typename T, char C >
struct push_front;

template < char ... Chars, char C >
struct push_front<char_sequence<Chars...>, C> {
    using type = char_sequence<C, Chars...>;
};

//----------------------------------------------------------------------------

template < typename T, typename U >
struct includes;

template < char MinA, char MaxA, char MinB, char MaxB >
struct includes< char_range< MinA, MaxA >, char_range< MinB, MaxB > > {
    using type = ::std::integral_constant< bool, ( MinA <= MinB && MaxB <= MaxA ) >;
};

template < typename T, typename U >
struct overlaps;

template < char MinA, char MaxA, char MinB, char MaxB >
struct overlaps <char_range< MinA, MaxA >, char_range< MinB, MaxB > > {
    using type = ::std::integral_constant< bool, !( MaxA < MinB || MaxB < MinA ) >;
};

//----------------------------------------------------------------------------
template < typename ... T >
struct join;

template < typename T >
struct join < T > {
    using type = T;
};

template < typename T, typename U, typename ... V >
struct join< T, U, V... >
    : join< typename join< T, U >::type, V... > {};

template < typename T, T ... A, T... B >
struct join< ::std::integer_sequence<T, A...>, ::std::integer_sequence<T, B...> > {
    using type = ::std::integer_sequence<T, A..., B...>;
};

template < char ... A, char ... B >
struct join< char_sequence<A...>, char_sequence<B...> > {
    using type = char_sequence<A..., B...>;
};

namespace detail {

template < bool, typename T, T ifTrue, T ifFalse >
struct conditional_c : ::std::integral_constant<T, ifTrue> {};

template < typename T, T ifTrue, T ifFalse >
struct conditional_c< false, T, ifTrue, ifFalse > : ::std::integral_constant<T, ifFalse> {};

constexpr ::std::size_t
strlen(char const* str)
{
    ::std::size_t sz = 0;
    for (; *str != 0; ++sz, ++str);
    return sz;
}

constexpr char
min(char a, char b)
{ return a < b ? a : b; }

constexpr char
max(char a, char b)
{ return a > b ? a : b; }


template < char const* Str, typename T >
struct make_char_sequence_impl;

template < char const* Str, ::std::size_t ... Indexes >
struct make_char_sequence_impl<Str, ::std::integer_sequence< ::std::size_t, Indexes... >> {
    using type = char_sequence< Str[Indexes]... >;
};

template < char Min, char Max, char ... Chars >
struct unwrap_char_range {
    static_assert(Min < Max, "Starting char of the range must be less than ending");
    using type = typename unwrap_char_range< Min, Max - 1, Max, Chars... >::type;
};

template < char C, char ... Chars >
struct unwrap_char_range< C, C, Chars ... > {
    using type = char_sequence<C, Chars...>;
};

template < typename T, T Min, T Max, T ... Values >
struct unwrap_range_impl {
    static_assert(Min < Max, "Start of range must be less than ending");
    using type = typename unwrap_range_impl<T, Min, Max - 1, Max, Values ... >::type;
};

template < typename T, T V, T ... Values >
struct unwrap_range_impl<T, V, V, Values...> {
    using type = ::std::integer_sequence< T, V, Values... >;
};

template < typename T, T Min, T Max, T ... Values >
struct reverse_unwrap_range_impl {
    static_assert(Min < Max, "Start of range must be less than ending");
    using type = typename reverse_unwrap_range_impl<T, Min + 1, Max, Min, Values ... >::type;
};

template < typename T, T V, T ... Values >
struct reverse_unwrap_range_impl<T, V, V, Values...> {
    using type = ::std::integer_sequence< T, V, Values... >;
};


const ::std::size_t template_depth = 128;

template < typename T, T Min, T Max >
struct unwrap_range;
template < typename T, T Min, T Max >
struct reverse_unwrap_range;

template < typename T, T Min, T Max >
struct split_range_helper {
    using type = typename join<
            typename unwrap_range_impl<T, Min, Min + template_depth - 1>::type,
            typename unwrap_range<T, Min + template_depth, Max>::type
    >::type;
};

template < typename T, T Min, T Max >
struct unwrap_range :
    ::std::conditional< (Max - Min < template_depth),
         unwrap_range_impl<T, Min, Max>,
         split_range_helper<T, Min, Max>
    >::type {};

template < typename T, T Min, T Max >
struct reverse_split_range_helper {
    using type = typename join<
            typename reverse_unwrap_range<T, Min + template_depth, Max>::type,
            typename reverse_unwrap_range_impl<T, Min, Min + template_depth - 1>::type
    >::type;
};
template < typename T, T Min, T Max >
struct reverse_unwrap_range :
    ::std::conditional< (Max - Min < template_depth),
         reverse_unwrap_range_impl<T, Min, Max>,
         reverse_split_range_helper<T, Min, Max>
    >::type {};

template < typename IndexTuple, template < char > class Predicate,
        typename V, V ifTrue, V ifFalse = V{} >
struct build_sort_table;

template < ::std::size_t ... Indexes, template < char > class Predicate,
    typename V, V ifTrue, V ifFalse >
struct build_sort_table<::std::integer_sequence< ::std::size_t, Indexes... >,
        Predicate, V, ifTrue, ifFalse > {

    using size = ::std::integral_constant<::std::size_t, sizeof ... (Indexes)>;
    using type = ::std::integer_sequence< V,
            (Predicate< (char)Indexes >::value ? ifTrue : ifFalse) ... >;
    static constexpr V value[] {
        (Predicate< (char)Indexes >::value ? ifTrue : ifFalse) ...
    };
};

using char_index_type = typename unwrap_range <::std::size_t, 0, 255>::type;
using char_reverse_index_type = typename reverse_unwrap_range<::std::size_t, 0, 255>::type;

template < typename T, typename Index >
struct make_char_sort_table;

template < char ... Chars, typename Index >
struct make_char_sort_table<char_sequence<Chars...>, Index> {
    using charset       = char_sequence<Chars...>;
    template < char C >
    using predicate     = contains<charset, C>;
    using type          = typename build_sort_table<Index,
                            predicate, bool, true, false>::type;
};

template < unsigned char N, typename T, char ... Chars >
struct sort_helper;

template < unsigned char N, bool V, bool ... Vals, char ... Chars >
struct sort_helper<N, ::std::integer_sequence<bool, V, Vals...>, Chars... > {
    using type = typename ::std::conditional<V,
            sort_helper<N - 1, ::std::integer_sequence<bool, Vals...>, char(N), Chars...>,
            sort_helper<N - 1, ::std::integer_sequence<bool, Vals...>, Chars...>
        >::type::type;
};

template < unsigned char N, bool V, char ... Chars >
struct sort_helper< N, ::std::integer_sequence<bool, V >, Chars ... > {
    using type = typename ::std::conditional<V,
            char_sequence< char(N), Chars... >,
            char_sequence< Chars... >
        >::type;
};

} /* namespace detail */

//----------------------------------------------------------------------------
template < typename T >
struct unique_sort;

template < char ... Chars >
struct unique_sort<char_sequence<Chars...>> {
    using original_seq      = char_sequence<Chars...>;
    using low_index         = typename detail::reverse_unwrap_range<::std::size_t, 0, 127>::type;
    using high_index        = typename detail::reverse_unwrap_range<::std::size_t, 128, 255>::type;
    using low_table         = typename detail::make_char_sort_table<original_seq, low_index>::type;
    using high_table        = typename detail::make_char_sort_table<original_seq, high_index>::type;
    using low_sorted        = typename detail::sort_helper< 127, low_table >::type;
    using high_sorted       = typename detail::sort_helper< 127, high_table >::type;

    using type              = typename join< low_sorted, high_sorted >::type;
};

template < char A, char B, char C >
struct join< char_range<A, B>, char_range<B, C> > {
    using type = char_range< A, C >;
};

template < char A, char B, char C >
struct join< char_range<A, B>, char_range<B + 1, C> > {
    using type = char_range< A, C >;
};

template < char A, char B, char C >
struct join< char_range<B, C>, char_range<A, B> > {
    using type = char_range< A, C >;
};

template < char A, char B, char C >
struct join< char_range<B + 1, C>, char_range<A, B> > {
    using type = char_range< A, C >;
};

namespace detail {

template < char A, char B, char C, char D, bool >
struct overlapping_range_join {
    using type = char_range< min(A, C), max(B, D) >;
};

template < char A, char B, char C, char D >
struct overlapping_range_join< A, B, C, D, false > {
    using type = typename unique_sort<
            typename join<
                typename unwrap_char_range< A, B >::type,
                typename unwrap_char_range< C, D >::type
            >::type
        >::type;
};

}  /* namespace detail */

template < char A, char B, char C, char D >
struct join< char_range<A, B>, char_range<C, D> >
    : detail::overlapping_range_join< A, B, C, D,
            overlaps< char_range<A, B>,
                char_range<C, D>>::type::value > {};

//----------------------------------------------------------------------------
template < char A, char B >
struct join< char_range<A, B>, char_sequence<> > {
    using type = char_range<A, B>;
};

template < char A, char B, char ... Chars >
struct join< char_range<A, B>, char_sequence<Chars...> > {
    using type = typename unique_sort<
            typename join<
                typename detail::unwrap_char_range< A, B >::type,
                char_sequence< Chars... >
            >::type
        >::type;
};

template < char A, char B >
struct join< char_sequence<>, char_range<A, B> > {
    using type = char_range<A, B>;
};

template < char ... Chars, char A, char B >
struct join< char_sequence<Chars...>, char_range<A, B> > {
    using type = typename unique_sort<
            typename join<
                typename detail::unwrap_char_range< A, B >::type,
                char_sequence< Chars... >
            >::type
        >::type;
};

//----------------------------------------------------------------------------
template < char const* Str >
using make_char_sequence = typename detail::make_char_sequence_impl<Str,
                                ::std::make_index_sequence<detail::strlen(Str)>>::type;


template < typename Charset, typename T, T Value, T Default = T{} >
struct char_class {
    using charset = Charset;
    template < char C >
    struct class_of : detail::conditional_c< contains< charset, C >::value, T, Value, Default > {};
};


} /* namespace hgcmp */



#endif /* HGCMP_EXPERIMENTAL_CHAR_CLASSIFICATION_HPP_ */
