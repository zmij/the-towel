/*
 * fibonacci.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: zmij
 */

#include <gtest/gtest.h>
#include <hgcm/fibonacci.hpp>

namespace hgcmp {

TEST(Fibonacci, Pass)
{
    ::testing::StaticAssertTypeEq<
         fibonacci<0>::type,
         ::std::integral_constant<::std::size_t, 0> >();
    ::testing::StaticAssertTypeEq<
         fibonacci<2>::type,
         ::std::integral_constant<::std::size_t, 1> >();
    ::testing::StaticAssertTypeEq<
         fibonacci<11>::type,
         ::std::integral_constant<::std::size_t, 89> >();
    ::testing::StaticAssertTypeEq<
         fibonacci<20>::type,
         ::std::integral_constant<::std::size_t, 6765> >();
}

}  /* namespace hgcm */

