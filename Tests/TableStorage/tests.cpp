// Copyright 2022 MOND

#include "Tests_Storage_Create.h"
#include "Tests_Storage_Delete.h"
#include "Tests_Storage_Get.h"
#include "Tests_Storage_GetKeys.h"

#include <gtest/gtest.h>

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
