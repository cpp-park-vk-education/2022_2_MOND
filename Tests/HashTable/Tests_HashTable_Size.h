// Copyright 2022 mora

#include "help_for_tests.h"

class DB_SIZE_TESTS : public testing::Test {
protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable(defaultHash);
    }

    void TearDown() override{
        delete quadratic;
    }

    std::vector<uint8_t> value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};
    IHashTable *quadratic = nullptr;
};

TEST_F(DB_SIZE_TESTS, Size_one_node) {
    quadratic->Insert({0x00, 0x01}, value);
    EXPECT_EQ(quadratic->GetSize(), 1);
}

TEST_F(DB_SIZE_TESTS, Size_before_grow_nodes) {
    quadratic->Insert({0x00, 0x01}, value);
    quadratic->Insert({0x00, 0x02}, value);
    quadratic->Insert({0x00, 0x03}, value);
    quadratic->Insert({0x00, 0x04}, value);
    quadratic->Insert({0x00, 0x05}, value);
    quadratic->Insert({0x00, 0x06}, value);
    EXPECT_EQ(quadratic->GetSize(), 6);
}

TEST_F(DB_SIZE_TESTS, Size_after_grow_nodes) {
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
    EXPECT_EQ(quadratic->GetSize(), 10);
}

TEST_F(DB_SIZE_TESTS, Size_same_nodes) {
    quadratic->Insert({0x00, 0x01}, value);
    quadratic->Insert({0x00, 0x01}, value);
    EXPECT_EQ(quadratic->GetSize(), 1);
}
