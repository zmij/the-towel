/*
 * iostreamable.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Sergei Fedorov
 */

#include <gtest/gtest.h>
#include <hgcmp/vol1/iostreamable.hpp>

namespace hgcmp {

struct __not_streamable {};

TEST(Traits, IOStreamable)
{
    EXPECT_TRUE( has_input_operator<int>::type::value )
        << "Int has an input operator";
    EXPECT_TRUE( has_output_operator<int>::type::value )
        << "Int has an output operator";
    EXPECT_FALSE( has_input_operator<__not_streamable>::type::value )
        << "Test structure doesn't have an input operator";
    EXPECT_FALSE( has_output_operator<__not_streamable>::type::value )
        << "Test structure doesn't have an input operator";
    EXPECT_TRUE( second::has_input_operator<int>::type::value )
        << "Int has an input operator";
    EXPECT_TRUE( second::has_output_operator<int>::type::value )
        << "Int has an output operator";
    EXPECT_FALSE( second::has_input_operator<__not_streamable>::type::value )
        << "Test structure doesn't have an input operator";
    EXPECT_FALSE( second::has_output_operator<__not_streamable>::type::value )
        << "Test structure doesn't have an input operator";
}

} // namespace test
