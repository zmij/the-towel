/*
 * is_metafunction.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: zmij
 */

#include <gtest/gtest.h>
#include <hgcmp/vol1/is_metafunction.hpp>

namespace hgcmp {

struct not_a_metafunction{};

TEST(Traits, IsMetafunction)
{
    ::testing::StaticAssertTypeEq<
             is_metafunction<::std::true_type>::type,
             ::std::true_type
         >();
    ::testing::StaticAssertTypeEq<
             is_metafunction<::std::false_type>::type,
             ::std::true_type
         >();
    ::testing::StaticAssertTypeEq<
             is_metafunction<not_a_metafunction>::type,
             ::std::false_type
         >();
    EXPECT_TRUE(is_metafunction<::std::true_type>::type::value);
    EXPECT_TRUE(is_metafunction<::std::false_type>::type::value);
    EXPECT_FALSE(is_metafunction<not_a_metafunction>::type::value);
}

}  /* namespace hgcm */
