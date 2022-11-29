// Copyright 2022 MOND

//#include "Tests_TableStorage.h"
#include "Tests_HashTable_Clear.h"
#include "Tests_HashTable_Find.h"
#include "Tests_HashTable_Get.h"
#include "Tests_HashTable_Insert.h"
#include "Tests_HashTable_Remove.h"
#include "Tests_HashTable_Size.h"
#include "Tests_HashTable_Update.h"

#include <gtest/gtest.h>

TEST(Test, test_for_test) { EXPECT_TRUE(true); }

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
