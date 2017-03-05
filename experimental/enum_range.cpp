/*
 * enum_range.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: zmij
 */

#include <gtest/gtest.h>
#include <hgcmp/experimental/enum_range.hpp>
#include <iostream>

namespace hgcmp {
namespace test {

enum powers {
    zero    = 1,
    one     = 2,
    two     = 4,
    three   = 8,
    four    = 16
};
} /* namespace test */

template <>
struct enum_traits< test::powers > : enum_traits_base<test::powers> {
    using enumerators = detail::enumerators<test::powers,
            test::zero, test::one, test::two, test::three, test::four>;
};

namespace test {

TEST(EnumRange, FullRange)
{
    for (auto e : enum_range< powers >()) {
        ::std::cerr << e << "\n";
    }
}

TEST(EnumRange, PartRange)
{
    for (auto e: enum_range(zero, two)) {
        ::std::cerr << e << "\n";
    }
    std::cerr << "---\n";

    for (auto e: enum_range(two, enum_end)) {
        ::std::cerr << e << "\n";
    }
    std::cerr << "---\n";

    for (auto e: enum_range(enum_begin, three)) {
        ::std::cerr << e << "\n";
    }
}

} /* namespace test */
} /* namespace hgcmp */

