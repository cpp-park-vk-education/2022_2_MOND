// Copyright 2022 MOND

#include "Tests_Storage_Create.h"
#include "Tests_Storage_Delete.h"
#include "Tests_Storage_Get.h"

#include <gtest/gtest.h>

TEST(Test, test_for_test) { EXPECT_TRUE(true); }

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
