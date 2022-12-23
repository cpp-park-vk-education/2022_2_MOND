// Copyright 2022 mora

#include "help_for_tests.h"

class DB_GET_TESTS : public testing::Test {
   protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable<std::string,
                                              std::string>(
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

    std::string value = {0x00, 0x01, 0x02, 0x03, 0x04,
                                  0x05, 0x06, 0x07, 0x08, 0x09};
    IHashTable<std::string, std::string>* quadratic = nullptr;
};

TEST_F(DB_GET_TESTS, Get_one_node) {
    EXPECT_EQ(quadratic->Get({0x00, 0x01}), value);
}

TEST_F(DB_GET_TESTS, Get_all_nodes) {
    EXPECT_EQ(quadratic->Get({0x00, 0x01}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x02}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x03}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x04}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x05}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x06}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x07}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x08}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x09}), value);
    EXPECT_EQ(quadratic->Get({0x00, 0x0A}), value);
}

TEST_F(DB_GET_TESTS, Get_not_exist_nodes) {
    EXPECT_TRUE(quadratic->Get({0x00, 0x20}).empty());
}

//check equal func
