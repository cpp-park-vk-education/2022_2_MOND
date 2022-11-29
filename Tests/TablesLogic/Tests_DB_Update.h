// Copyright 2022 mora

#include "help_for_tests.h"

class DB_CHANGE_VALUE_TESTS : public testing::Test {
protected:
    void SetUp() override {
        quadratic = new QuadraticProbingTable(hash);

        auto key01 = new uint8_t[]{0x00, 0x01};
        auto key02 = new uint8_t[]{0x00, 0x02};
        auto key03 = new uint8_t[]{0x00, 0x03};
        auto key04 = new uint8_t[]{0x00, 0x04};
        auto key05 = new uint8_t[]{0x00, 0x05};
        auto key06 = new uint8_t[]{0x00, 0x06};
        auto key07 = new uint8_t[]{0x00, 0x07};
        auto key08 = new uint8_t[]{0x00, 0x08};
        auto key09 = new uint8_t[]{0x00, 0x09};
        auto key10 = new uint8_t[]{0x00, 0x0A};

        auto value = new uint8_t[]{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

        quadratic->Insert(key01, 2, value, 10);
        quadratic->Insert(key02, 2, value, 10);
        quadratic->Insert(key03, 2, value, 10);
        quadratic->Insert(key04, 2, value, 10);
        quadratic->Insert(key05, 2, value, 10);
        quadratic->Insert(key06, 2, value, 10);
        quadratic->Insert(key07, 2, value, 10);
        quadratic->Insert(key08, 2, value, 10);
        quadratic->Insert(key09, 2, value, 10);
        quadratic->Insert(key10, 2, value, 10);
    }

    void TearDown() override {
        delete quadratic;
    }

    IHashTable *quadratic = nullptr;
};

TEST_F(DB_CHANGE_VALUE_TESTS, Change_value_one_node) {
    auto key01 = new uint8_t[]{0x00, 0x01};
    auto value = new uint8_t[]{0x12, 0x12, 0x12, 0x12, 0x12, 0x05, 0x06, 0x07, 0x08, 0x09};

    EXPECT_TRUE(quadratic->Update(key01, 2, value, 10));

    EXPECT_TRUE(!memcmp(quadratic->Get(key01, 2), value, 10));
}

TEST_F(DB_CHANGE_VALUE_TESTS, Change_value_all_nodes) {
    auto key01 = new uint8_t[]{0x00,0x01};
    auto key02 = new uint8_t[]{0x00,0x02};
    auto key03 = new uint8_t[]{0x00,0x03};
    auto key04 = new uint8_t[]{0x00,0x04};
    auto key05 = new uint8_t[]{0x00,0x05};
    auto key06 = new uint8_t[]{0x00,0x06};
    auto key07 = new uint8_t[]{0x00,0x07};
    auto key08 = new uint8_t[]{0x00,0x08};
    auto key09 = new uint8_t[]{0x00,0x09};
    auto key10 = new uint8_t[]{0x00,0x0A};

    auto value = new uint8_t[]{0x12, 0x12, 0x12, 0x12, 0x12, 0x05, 0x06, 0x07, 0x08, 0x09};

    EXPECT_TRUE(quadratic->Update(key01, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key02, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key03, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key04, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key05, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key06, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key07, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key08, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key09, 2, value, 10));
    EXPECT_TRUE(quadratic->Update(key10, 2, value, 10));

    EXPECT_TRUE(!memcmp(quadratic->Get(key01, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key02, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key03, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key04, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key05, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key06, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key07, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key08, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key09, 2), value, 10));
    EXPECT_TRUE(!memcmp(quadratic->Get(key10, 2), value, 10));
}

TEST_F(DB_CHANGE_VALUE_TESTS, Change_value_not_exist_nodes) {
    auto key01 = new uint8_t[]{0x00, 0x11};
    auto value = new uint8_t[]{0x12, 0x12, 0x12, 0x12, 0x12, 0x05, 0x06, 0x07, 0x08, 0x09};

    EXPECT_FALSE(quadratic->Update(key01, 2,  value, 10));
}
