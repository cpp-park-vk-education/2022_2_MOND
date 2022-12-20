// Copyright 2022 MOND

#include <gtest/gtest.h>
#include "Tests_IStorageUsageByWorker.h"
#include "Tests_ITableUsageByWorker.h"


int main() {
    ::testing::InitGoogleTest();
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
