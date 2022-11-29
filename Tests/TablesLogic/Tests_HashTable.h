// Copyright 2022 mora

#include "help_for_tests.h"
//#include "ITableStorage.h"
#include "TableStorage.h"
#include "IHashTable.h"
#include "QuadraticProbingTable.h"
#include "Hashes.h"

class HashTable_Tests : public testing::Test {
protected:
    void SetUp() override {
        key = new uint8_t[2];
        value = new uint8_t[2];
        ts = new TableStorage(10);
        ts->CreateTable("Table01");
        table = ts->GetTable("Table01");
    }

    ITableStorage *ts;
    IHashTable *table;
    uint8_t *key;
    uint8_t *value;
};

TEST_F(HashTable_Tests, Insert_Success) {
    EXPECT_EQ(table->Insert(key, 2, value, 2), true);
}

TEST_F(HashTable_Tests, Insert_Failure) {
    EXPECT_EQ(table->Insert(key, 2, value, 2), false);
}

TEST_F(HashTable_Tests, Remove_Success) {
    table->Insert(key, 2, value, 2);
    EXPECT_EQ(table->Remove(key, 2), true);
}

TEST_F(HashTable_Tests, Remove_Failure) {
    EXPECT_EQ(table->Remove(key, 2), false);
}

TEST_F(HashTable_Tests, Find_Success) {
    table->Insert(key, 2, value, 2);
    EXPECT_EQ(table->Find(key, 2), true);
}

TEST_F(HashTable_Tests, Find_Failure) {
    EXPECT_EQ(table->Find(key, 2), false);
}

TEST_F(HashTable_Tests, Clear_Success) {
    table->Insert(key, 2, value, 2);
    table->Clear();

    EXPECT_EQ(table->GetSize(), 0);
}

TEST_F(HashTable_Tests, Get_Success) {
    table->Insert(key, 2, value, 2);
    auto elem = table->Get(key, 2);

    EXPECT_EQ(memcmp(elem, value, 2), true);
}

TEST_F(HashTable_Tests, Get_Failure) {
    auto elem = table->Get(key, 2);

    EXPECT_EQ(elem, nullptr);
}

TEST_F(HashTable_Tests, Update_Success) {
    table->Insert(key, 2, value, 2);

    EXPECT_EQ(table->Update(key, 2, value, 2), true);
}

TEST_F(HashTable_Tests, Update_Failure) {
    EXPECT_EQ(table->Update(key, 2, value, 2), false);
}
