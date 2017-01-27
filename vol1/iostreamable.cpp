/*
 * iostreamable.cpp
 *
 *  Created on: 26 янв. 2017 г.
 *      Author: sergey.fedorov
 */

#include <gtest/gtest.h>
#include <hgcm/vol1/iostreamable.hpp>

namespace hgcm {

struct __not_streamable {};

TEST(Traits, IOStreamable)
{
    EXPECT_TRUE( has_input_operator<int>::type::value )
        << "Int has an input operator";
    EXPECT_TRUE( has_output_operator<int>::type::value )
        << "Int has an output operator";
    EXPECT_TRUE( has_input_operator<int>::value )
        << "Int has an input operator";
    EXPECT_TRUE( has_output_operator<int>::value )
        << "Int has an output operator";
    EXPECT_FALSE( has_input_operator<__not_streamable>::value )
        << "Test structure doesn't have an input operator";
    EXPECT_FALSE( has_output_operator<__not_streamable>::value )
        << "Test structure doesn't have an input operator";
}

} // namespace test
