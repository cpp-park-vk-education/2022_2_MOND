// Copyright 2022 MOND

#include "Tests_HashTable.h"
#include "Tests_TableStorage.h"

#include <gtest/gtest.h>

TEST(Test, test_for_test) { EXPECT_TRUE(true); }

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
