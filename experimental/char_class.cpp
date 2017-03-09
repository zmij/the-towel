/*
 * char_class.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: zmij
 */

#include <gtest/gtest.h>

#include <hgcmp/experimental/char_class.hpp>

namespace hgcmp {

enum class char_classes {
    unassigned  = 0x00,
    horz_space  = 0x01,
    vert_space  = 0x02,
    whitespace  = horz_space | vert_space,
    alpha       = 0x04,
    digits      = 0x08,
    alnum       = alpha | digits,
    oct_digits  = 0x10,
    hex_digits  = 0x20,

    sub_delims  = 0x40,
    gen_delims  = 0x80
};

constexpr char_classes
operator | (char_classes lhs, char_classes rhs)
{
    using int_type = ::std::underlying_type<char_classes>::type;
    return static_cast<char_classes>( static_cast<int_type>(lhs) | static_cast<int_type>(rhs) );
}

constexpr char_classes
operator & (char_classes lhs, char_classes rhs)
{
    using int_type = ::std::underlying_type<char_classes>::type;
    return static_cast<char_classes>( static_cast<int_type>(lhs) & static_cast<int_type>(rhs) );
}

constexpr bool
any(char_classes v)
{
    using int_type = ::std::underlying_type<char_classes>::type;
    return (static_cast<char_classes>(~int_type{0}) & v) != char_classes::unassigned;
}

template < typename Charset, char_classes Class >
using char_classification = char_class< Charset, char_classes, Class ,char_classes::unassigned >;

namespace {

constexpr char sub_delims[]   = "!$&'()*+,;=";
constexpr char gen_delims[]   = ":/?#[]@";

} /* namespace  */

using horizontal_space      = char_sequence< ' ', '\t' >;
using vertical_space        = char_sequence< '\r', '\n', '\v' >;
using whitespace            = join< horizontal_space, vertical_space >::type;
using latin_upper           = char_range< 'A', 'Z' >;
using latin_lower           = char_range< 'a', 'z' >;
using alpha                 = join< latin_upper, latin_lower >::type;
using digits                = char_range< '0', '9' >;
using alnum                 = join< alpha, digits >::type;

using oct_digits            = char_range< '0', '7' >;
using hex_digits            = join< digits, char_range<'A', 'F'>,
                                            char_range<'a', 'f'> >::type;

using horz_space_class      = char_classification< horizontal_space, char_classes::horz_space >;
using vert_space_class      = char_classification< vertical_space, char_classes::vert_space >;
using alpha_chars_class     = char_classification< alpha, char_classes::alpha >;
using digits_class          = char_classification< digits, char_classes::digits >;
//using sub_delims_class  = char_classification< sub_delims, char_classes::sub_delims>;
//using gen_delims_class  = char_classification< gen_delims, char_classes::gen_delims >;

} /* namespace hgcmp */

