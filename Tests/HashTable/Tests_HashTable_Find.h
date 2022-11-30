// Copyright 2022 mora

#include "help_for_tests.h"

class DB_FIND_TESTS : public testing::Test {
   protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable(defaultHash);

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
    IHashTable* quadratic = nullptr;
};

TEST_F(DB_FIND_TESTS, Find_one_node) {
    EXPECT_TRUE(quadratic->Find({0x00, 0x01}));
}

TEST_F(DB_FIND_TESTS, Find_all_nodes) {
    EXPECT_TRUE(quadratic->Find({0x00, 0x01}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x02}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x03}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x04}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x05}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x06}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x07}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x08}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x09}));
    EXPECT_TRUE(quadratic->Find({0x00, 0x0A}));
}

TEST_F(DB_FIND_TESTS, Find_not_exist_nodes) {
    EXPECT_FALSE(quadratic->Find({0x00, 0xFF}));
}
