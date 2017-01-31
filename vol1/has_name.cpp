/*
 * has_name.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: zmij
 */

#include <gtest/gtest.h>
#include <hgcm/vol1/has_name.hpp>

namespace hgcmp {

struct named_struct {
    int name;
};

struct no_name_struct {};

TEST(Traits, HasName)
{
    ::testing::StaticAssertTypeEq<
             has_name<named_struct>::type,
             ::std::true_type
         >();
    ::testing::StaticAssertTypeEq<
             has_name<no_name_struct>::type,
             ::std::false_type
         >();
    EXPECT_TRUE(has_name<named_struct>::type::value);
    EXPECT_FALSE(has_name<no_name_struct>::type::value);
}

}  /* namespace hgcmp */
