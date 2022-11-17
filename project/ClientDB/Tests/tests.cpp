// Copyright 2022 MOND

#include <gtest/gtest.h>

#include "Connector.hpp"
#include "header.hpp"

TEST(Test_sum, A_plus_B) { EXPECT_EQ(sum(1, 2), 3); }

TEST(Test_mul, A_mul_B) {
    Connector conn;
    EXPECT_EQ(conn.mul(1, 2), 2);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
