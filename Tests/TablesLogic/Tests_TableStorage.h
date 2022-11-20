// Copyright 2022 mora

#include "help_for_tests.h"
#include "ITableStorage.h"
#include "TableStorage.h"
#include "IHashTable.h"
#include "QuadraticProbingTable.h"
#include "Hashes.h"

class Table_Tests : public testing::Test {
protected:
    ITableStorage *ts = new TableStorage(10);
};

TEST_F(Table_Tests, Create_Table_Success) {
    ts->CreateTable("Table01");

    EXPECT_EQ(ts->GetNumTables(), 1);
}

TEST_F(Table_Tests, Create_Table_Failure) {
    ts->CreateTable("Table01");
    ts->CreateTable("Table01");

    EXPECT_EQ(ts->CreateTable("Table01"), false);
}

TEST_F(Table_Tests, Delete_Table_Success) {
    ts->CreateTable("Table01");
    ts->DeleteTable("Table01");

    EXPECT_EQ(ts->GetNumTables(), 0);
}

TEST_F(Table_Tests, Delete_Table_Failure) {
    ts->CreateTable("Table01");
    ts->DeleteTable("Table01");

    EXPECT_EQ(ts->DeleteTable("Table01"), false);
}

TEST_F(Table_Tests, Show_Table_Success) {
    ts->CreateTable("Table01");
    auto tables = ts->ShowTables();

    EXPECT_EQ(tables.size(), 1);
}

TEST_F(Table_Tests, Show_Table_Failure) {
    auto tables = ts->ShowTables();

    EXPECT_EQ(tables.size(), 0);
}

TEST_F(Table_Tests, Get_Table_Success) {
    ts->CreateTable("Table01");
    auto table = ts->GetTable("Table01");

    EXPECT_EQ(table->GetSize(), 0);
}

TEST_F(Table_Tests, Get_Table_Failure) {
    auto table = ts->GetTable("Table01");

    EXPECT_EQ(table, nullptr);
}
