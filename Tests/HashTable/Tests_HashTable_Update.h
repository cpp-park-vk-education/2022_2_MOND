// Copyright 2022 mora

#include "help_for_tests.h"

class DB_CHANGE_VALUE_TESTS : public testing::Test {
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
        quadratic->Insert({0x00, 0x0A}, value);
    }

    void TearDown() override { delete quadratic; }

    std::vector<uint8_t> value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};

    std::vector<uint8_t> value_new = {0x12, 0x12, 0x12, 0x12, 0x12,
                                      0x12, 0x12, 0x12, 0x12, 0x12};
    IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* quadratic = nullptr;
};

TEST_F(DB_CHANGE_VALUE_TESTS, Change_value_one_node) {
    EXPECT_TRUE(quadratic->Update({0x00, 0x01}, value_new));
    EXPECT_EQ(quadratic->Get({0x00, 0x01}), value_new);
}

TEST_F(DB_CHANGE_VALUE_TESTS, Change_value_all_nodes) {
    EXPECT_TRUE(quadratic->Update({0x00, 0x01}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x02}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x03}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x04}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x05}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x06}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x07}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x08}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x09}, value_new));
    EXPECT_TRUE(quadratic->Update({0x00, 0x0A}, value_new));

    EXPECT_EQ(quadratic->Get({0x00, 0x01}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x02}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x03}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x04}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x05}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x06}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x07}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x08}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x09}), value_new);
    EXPECT_EQ(quadratic->Get({0x00, 0x0A}), value_new);
}

TEST_F(DB_CHANGE_VALUE_TESTS, Change_value_not_exist_nodes) {
    EXPECT_FALSE(quadratic->Update({0x00, 0xFF}, value_new));
}
