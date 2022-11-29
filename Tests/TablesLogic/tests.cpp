// Copyright 2022 MOND

//#include "Tests_HashTable.h"
//#include "Tests_TableStorage.h"
#include "Tests_DB_Clear.h"
#include "Tests_DB_Find.h"
#include "Tests_DB_Get.h"
#include "Tests_DB_Insert.h"
#include "Tests_DB_Remove.h"
#include "Tests_DB_Size.h"
#include "Tests_DB_Update.h"

#include <gtest/gtest.h>

TEST(Test, test_for_test) { EXPECT_TRUE(true); }

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
