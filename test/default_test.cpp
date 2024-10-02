#include <gtest/gtest.h>
#include "header.hpp"

TEST(default_test, tests_working)
{
    EXPECT_EQ(test(3), 6);
};