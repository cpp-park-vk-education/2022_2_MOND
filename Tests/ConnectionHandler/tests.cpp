// Copyright 2022 MOND

#include <gtest/gtest.h>
#include "Tests_ConnectionHandler.h"
#include "Tests_Worker.h"
#include "Tests_WorkerFactory.h"


TEST(Test, test_for_test) { EXPECT_TRUE(true); }

int main() {
    ::testing::InitGoogleTest();
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
