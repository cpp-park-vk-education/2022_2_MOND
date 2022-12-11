// Copyright 2022 MOND

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Initializer.h"


TEST(Test, test_for_test) {
    EXPECT_TRUE(true);
}

int main() {
    ::testing::InitGoogleTest();

    Initializer dataBase;
    dataBase.startDB(2);
    dataBase.handleCommands();
    dataBase.stopDB();

    return RUN_ALL_TESTS();
}
