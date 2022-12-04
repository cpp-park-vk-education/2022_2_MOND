// Copyright 2022 mora

#include "help_for_tests.h"

class DB_CLEAR_TESTS : public testing::Test {
   protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable<std::vector<uint8_t>,
                                                       std::vector<uint8_t>>(
            defaultHash);
    }

    void TearDown() override { delete quadratic; }

    std::vector<uint8_t> value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};
    IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* quadratic = nullptr;
};

TEST_F(DB_CLEAR_TESTS, Clear_one_node) {
    quadratic->Insert({0x00, 0x01}, value);
    EXPECT_EQ(quadratic->GetSize(), 1);

    quadratic->Clear();
    EXPECT_EQ(quadratic->GetSize(), 0);
}

TEST_F(DB_CLEAR_TESTS, Clear_before_grow_nodes) {
    quadratic->Insert({0x00, 0x01}, value);
    quadratic->Insert({0x00, 0x02}, value);
    quadratic->Insert({0x00, 0x03}, value);
    quadratic->Insert({0x00, 0x04}, value);
    quadratic->Insert({0x00, 0x05}, value);
    quadratic->Insert({0x00, 0x06}, value);
    EXPECT_EQ(quadratic->GetSize(), 6);

    quadratic->Clear();
    EXPECT_EQ(quadratic->GetSize(), 0);
}

TEST_F(DB_CLEAR_TESTS, Clear_after_grow_nodes) {
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

    quadratic->Clear();
    EXPECT_EQ(quadratic->GetSize(), 0);
}

TEST_F(DB_CLEAR_TESTS, Clear_same_nodes) {
    quadratic->Insert({0x00, 0x01}, value);
    quadratic->Insert({0x00, 0x01}, value);
    EXPECT_EQ(quadratic->GetSize(), 1);

    quadratic->Clear();
    EXPECT_EQ(quadratic->GetSize(), 0);
}
