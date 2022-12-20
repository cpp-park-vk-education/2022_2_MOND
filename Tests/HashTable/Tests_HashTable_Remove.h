// Copyright 2022 mora

#include "help_for_tests.h"

class DB_REMOVE_TESTS : public testing::Test {
   protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable<std::vector<uint8_t>,
                                                       std::vector<uint8_t>>(
            defaultHash);

        quadratic->Insert({0x00, 0x01}, value);
        quadratic->Insert({0x00, 0x02}, value);
        quadratic->Insert({0x00, 0x03}, value);
        quadratic->Insert({0x00, 0x04}, value);
        quadratic->Insert({0x00, 0x05}, value);
        quadratic->Insert({0x00, 0x06}, value);
        quadratic->Insert({0x00, 0x07}, value);
        quadratic->Insert({0x00, 0x08}, value);
        quadratic->Insert({0x00, 0x09}, value);
        quadratic->Insert({0x00, 0x10}, value);
    }

    void TearDown() override { delete quadratic; }

    std::vector<uint8_t> value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};
    IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* quadratic = nullptr;
};

TEST_F(DB_REMOVE_TESTS, Remove_one_node) {
    EXPECT_TRUE(quadratic->Remove({0x00, 0x01}));
}

TEST_F(DB_REMOVE_TESTS, Remove_all_nodes) {
    EXPECT_TRUE(quadratic->Remove({0x00, 0x01}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x02}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x03}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x04}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x05}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x06}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x07}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x08}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x09}));
    EXPECT_TRUE(quadratic->Remove({0x00, 0x10}));
}

TEST_F(DB_REMOVE_TESTS, Remove_same_nodes) {
    EXPECT_TRUE(quadratic->Remove({0x00, 0x01}));
    EXPECT_FALSE(quadratic->Remove({0x00, 0x01}));
}

TEST_F(DB_REMOVE_TESTS, Remove_not_exist_nodes) {
    EXPECT_FALSE(quadratic->Remove({0x00, 0xFF}));
}
