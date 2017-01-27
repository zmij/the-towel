/*
 * has_call_operator.cpp
 *
 *  Created on: Jan 26 2017
 *      Author: Sergei Fedorov
 */

#include <gtest/gtest.h>
#include <hgcm/vol1/has_call_operator.hpp>

namespace hgcm {

struct with_call_operator {
    void
    operator()();
};
struct no_call_operator {};


TEST(Traits, CallOperator)
{
    EXPECT_TRUE(has_call_operator<with_call_operator>::value)
        << "The call operator is there";
    EXPECT_FALSE(has_call_operator<no_call_operator>::value)
        << "The call operator is not there";
}

}  /* namespace hgcm */
