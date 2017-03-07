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
    alpha       = 0x01,
    digits      = 0x02,
    sub_delims  = 0x04,
    gen_delims  = 0x08
};

template < char const* Str, char_classes Class >
using char_classification = char_class< Str, char_classes, Class ,char_classes::unassigned >;

namespace {

constexpr char latin_upper[]  = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";
constexpr char latin_lower[]  = "abcdefghijklmnopqrstuvwxyz";
constexpr char digits[]       = "0123456789";
constexpr char sub_delims[]   = "!$&'()*+,;=";
constexpr char gen_delims[]   = ":/?#[]@";
constexpr char oct_digits[]   = "01234567";
constexpr char hex_digits[]   = "0123456789ABCDEFabcdef";

} /* namespace  */

using alpha_chars_class = char_classification< latin_lower, char_classes::alpha >;
using digits_class      = char_classification< digits, char_classes::digits >;
using sub_delims_class  = char_classification< sub_delims, char_classes::sub_delims>;
using gen_delims_class  = char_classification< gen_delims, char_classes::gen_delims >;

} /* namespace hgcmp */

