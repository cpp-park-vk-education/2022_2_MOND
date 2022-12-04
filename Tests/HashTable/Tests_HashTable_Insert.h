// Copyright 2022 mora

#include "help_for_tests.h"

class DB_INSERT_TESTS : public testing::Test {
protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable<std::vector<uint8_t>,
                                                       std::vector<uint8_t>>(
            defaultHash);
    }

    void TearDown() override{
        delete quadratic;
    }

    std::vector<uint8_t> value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};
    IHashTable<std::vector<uint8_t>, std::vector<uint8_t>> *quadratic = nullptr;
};

TEST_F(DB_INSERT_TESTS, Insert_one_node) {
    EXPECT_TRUE(quadratic->Insert({0x00, 0x01}, value));
}

TEST_F(DB_INSERT_TESTS, Insert_before_grow_nodes) {
    EXPECT_TRUE(quadratic->Insert({0x00, 0x01}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x02}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x03}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x04}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x05}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x06}, value));
}

TEST_F(DB_INSERT_TESTS, Insert_after_grow_nodes) {
    std::vector<uint8_t> value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};

    EXPECT_TRUE(quadratic->Insert({0x00, 0x01}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x02}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x03}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x04}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x05}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x06}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x07}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x08}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x09}, value));
    EXPECT_TRUE(quadratic->Insert({0x00, 0x0A}, value));
}

TEST_F(DB_INSERT_TESTS, Insert_same_nodes) {
    EXPECT_TRUE(quadratic->Insert({0x00, 0x01}, value));
    EXPECT_FALSE(quadratic->Insert({0x00, 0x01}, value));
}
