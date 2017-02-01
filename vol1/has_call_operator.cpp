/*
 * has_call_operator.cpp
 *
 *  Created on: Jan 26 2017
 *      Author: Sergei Fedorov
 */

#include <gtest/gtest.h>
#include <hgcm/vol1/has_call_operator.hpp>

namespace hgcmp {

namespace {
struct with_call_operator {
    void
    operator()();
};
struct no_call_operator {};

struct with_multiple_operator_overloads {
    void
    operator()();
    int
    operator()(int);
};

struct with_template_call_operator{
    template < typename T >
    void
    operator()(T);
};

struct with_variadic_call_operator{
    template < typename ... T >
    void
    operator()(T...);
};

struct with_reference_return_operator {
    int&
    operator()();
};


}  /* namespace  */

TEST(Traits, CallOperator)
{
    EXPECT_TRUE(has_call_operator<with_call_operator>::type::value)
        << "The call operator is there";
    EXPECT_FALSE(has_call_operator<no_call_operator>::type::value)
        << "The call operator is not there";
    EXPECT_FALSE(has_call_operator<with_multiple_operator_overloads>::type::value)
        << "The call operator is templated, thus not detected";
    EXPECT_FALSE(has_call_operator<with_template_call_operator>::type::value)
        << "The call operator is templated, thus not detected";
    EXPECT_FALSE(has_call_operator<with_variadic_call_operator>::type::value)
        << "The call operator is templated, thus not detected";

    EXPECT_FALSE(is_callable<no_call_operator>::type::value)
        << "The call operator is not there";
    EXPECT_TRUE(is_callable<with_multiple_operator_overloads>::type::value)
        << "The call operator without parameters is detected";
    EXPECT_TRUE((is_callable<with_template_call_operator, int>::type::value))
        << "The template operator can be checked";
    EXPECT_TRUE((is_callable<with_variadic_call_operator, int>::type::value))
        << "The template operator can be checked";
    EXPECT_TRUE((is_callable<with_variadic_call_operator>::type::value))
        << "The template operator can be checked";
    EXPECT_TRUE((is_callable<with_variadic_call_operator, int, long, float&, double*>::type::value))
        << "The template operator can be checked";

    EXPECT_TRUE(is_callable<with_reference_return_operator>::type::value)
        << "The call operator without parameters is detected";
}

}  /* namespace hgcm */
