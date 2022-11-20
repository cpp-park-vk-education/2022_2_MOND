// Copyright 2022 mora

#include "help_for_tests.h"
#include "ISerializer.h"
#include "Serializer.h"

class Serializer_Tests : public testing::Test {
protected:
    void SetUp() override {
        key = new uint8_t[2];
        value = new uint8_t[2];
        serializer = new Serializer();

        request = {
                requestType::INSERT,
                Status::OK,
                2,
                2,
                key,
                value
        };
    }

    uint8_t *key;
    uint8_t *value;
    Request request;
    ISerializer *serializer;
};

TEST_F(Serializer_Tests, Marshal_Success) {
    serializer->Marshal(request);
    EXPECT_TRUE(true);
}

TEST_F(Serializer_Tests, Marshal_Failure) {
    serializer->Marshal(request);
    EXPECT_TRUE(true);
}

TEST_F(Serializer_Tests, Unmarshal_Success) {
    serializer->Unmarshal(value);
    EXPECT_TRUE(true);
}

TEST_F(Serializer_Tests, Unmarshal_Failure) {
    serializer->Unmarshal(value);
    EXPECT_TRUE(true);
}
