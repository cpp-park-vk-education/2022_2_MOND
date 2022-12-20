// Copyright 2022 mora

#include "help_for_tests.h"

class Backupper_tests : public testing::Test {
protected:
    void SetUp() override {
        req01 = {requestType::INSERT, Status::NOTHING, key, value, table_name};
        req02 = {requestType::INSERT, Status::NOTHING, key, value, table_name2};

        b = new Backupper();
    }

    void TearDown() override{
        delete b;
    }

    Request req01;
    Request req02;
    std::vector<uint8_t> key = {0x01, 0x02};
    std::vector<uint8_t> value = {0x03, 0x04, 0x05};
    std::string table_name = "Table01";
    std::string table_name2 = "Table02";

    IBackupper *b = nullptr;
};

TEST_F(Backupper_tests, MakeBackup) {
    EXPECT_TRUE(b->MakeBackup(req01));
    EXPECT_TRUE(b->MakeBackup(req02));
}

TEST_F(Backupper_tests, ReadBackup) {
    auto result = b->ReadBackup();
    EXPECT_EQ(req01, result[0]);
    EXPECT_EQ(req02, result[1]);
}
