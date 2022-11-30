// Copyright 2022 mora

#include "help_for_tests.h"
#include "ITableStorage.h"
#include "TableStorage.h"
#include "IHashTable.h"
#include "QuadraticProbingTable.h"
#include "Hashes.h"

class STORAGE_GET_TESTS : public testing::Test {
protected:
    void SetUp() override {
        ITS = new TableStorage();
    }

    void TearDown() override{
        delete ITS;
    }

    ITableStorage *ITS = nullptr;
};

TEST_F(STORAGE_GET_TESTS, Get_one_table) {
    ITS->CreateTable("Table01");

    auto Table01 = ITS->GetTable("Table01");
    EXPECT_EQ(Table01->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_one_table_with_hash) {
    ITS->CreateTable("Table01", defaultHash);

    auto Table01 = ITS->GetTable("Table01");
    EXPECT_EQ(Table01->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_before_grow_nodes) {
    ITS->CreateTable("Table01");
    ITS->CreateTable("Table02");
    ITS->CreateTable("Table03");
    ITS->CreateTable("Table04");
    ITS->CreateTable("Table05");
    ITS->CreateTable("Table06");

    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01->GetSize(), 0);

    auto Table02 = ITS->GetTable("Table02");
    EXPECT_EQ(Table02->GetSize(), 0);

    auto Table03 = ITS->GetTable("Table03");
    EXPECT_EQ(Table03->GetSize(), 0);

    auto Table04 = ITS->GetTable("Table04");
    EXPECT_EQ(Table04->GetSize(), 0);

    auto Table05 = ITS->GetTable("Table05");
    EXPECT_EQ(Table05->GetSize(), 0);

    auto Table06 = ITS->GetTable("Table06");
    EXPECT_EQ(Table06->GetSize(), 0);

}

TEST_F(STORAGE_GET_TESTS, Get_before_grow_nodes_with_hash) {
    ITS->CreateTable("Table01", defaultHash);
    ITS->CreateTable("Table02", defaultHash);
    ITS->CreateTable("Table03", defaultHash);
    ITS->CreateTable("Table04", defaultHash);
    ITS->CreateTable("Table05", defaultHash);
    ITS->CreateTable("Table06", defaultHash);

    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01->GetSize(), 0);

    auto Table02 = ITS->GetTable("Table02");
    EXPECT_EQ(Table02->GetSize(), 0);

    auto Table03 = ITS->GetTable("Table03");
    EXPECT_EQ(Table03->GetSize(), 0);

    auto Table04 = ITS->GetTable("Table04");
    EXPECT_EQ(Table04->GetSize(), 0);

    auto Table05 = ITS->GetTable("Table05");
    EXPECT_EQ(Table05->GetSize(), 0);

    auto Table06 = ITS->GetTable("Table06");
    EXPECT_EQ(Table06->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_after_grow_nodes) {
    ITS->CreateTable("Table01");
    ITS->CreateTable("Table02");
    ITS->CreateTable("Table03");
    ITS->CreateTable("Table04");
    ITS->CreateTable("Table05");
    ITS->CreateTable("Table06");
    ITS->CreateTable("Table07");
    ITS->CreateTable("Table08");
    ITS->CreateTable("Table09");
    ITS->CreateTable("Table10");

    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01->GetSize(), 0);

    auto Table02 = ITS->GetTable("Table02");
    EXPECT_EQ(Table02->GetSize(), 0);

    auto Table03 = ITS->GetTable("Table03");
    EXPECT_EQ(Table03->GetSize(), 0);

    auto Table04 = ITS->GetTable("Table04");
    EXPECT_EQ(Table04->GetSize(), 0);

    auto Table05 = ITS->GetTable("Table05");
    EXPECT_EQ(Table05->GetSize(), 0);

    auto Table06 = ITS->GetTable("Table06");
    EXPECT_EQ(Table06->GetSize(), 0);

    auto Table07 = ITS->GetTable("Table07");
    EXPECT_EQ(Table07->GetSize(), 0);

    auto Table08 = ITS->GetTable("Table08");
    EXPECT_EQ(Table08->GetSize(), 0);

    auto Table09 = ITS->GetTable("Table09");
    EXPECT_EQ(Table09->GetSize(), 0);

    auto Table10 = ITS->GetTable("Table10");
    EXPECT_EQ(Table10->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_after_grow_nodes_with_hash) {
    ITS->CreateTable("Table01", defaultHash);
    ITS->CreateTable("Table02", defaultHash);
    ITS->CreateTable("Table03", defaultHash);
    ITS->CreateTable("Table04", defaultHash);
    ITS->CreateTable("Table05", defaultHash);
    ITS->CreateTable("Table06", defaultHash);
    ITS->CreateTable("Table07", defaultHash);
    ITS->CreateTable("Table08", defaultHash);
    ITS->CreateTable("Table09", defaultHash);
    ITS->CreateTable("Table10", defaultHash);

    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01->GetSize(), 0);

    auto Table02 = ITS->GetTable("Table02");
    EXPECT_EQ(Table02->GetSize(), 0);

    auto Table03 = ITS->GetTable("Table03");
    EXPECT_EQ(Table03->GetSize(), 0);

    auto Table04 = ITS->GetTable("Table04");
    EXPECT_EQ(Table04->GetSize(), 0);

    auto Table05 = ITS->GetTable("Table05");
    EXPECT_EQ(Table05->GetSize(), 0);

    auto Table06 = ITS->GetTable("Table06");
    EXPECT_EQ(Table06->GetSize(), 0);

    auto Table07 = ITS->GetTable("Table07");
    EXPECT_EQ(Table07->GetSize(), 0);

    auto Table08 = ITS->GetTable("Table08");
    EXPECT_EQ(Table08->GetSize(), 0);

    auto Table09 = ITS->GetTable("Table09");
    EXPECT_EQ(Table09->GetSize(), 0);

    auto Table10 = ITS->GetTable("Table10");
    EXPECT_EQ(Table10->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_same_nodes) {
    EXPECT_TRUE(ITS->CreateTable("Table01"));
    EXPECT_FALSE(ITS->CreateTable("Table01"));

    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_same_nodes_with_hash) {
    EXPECT_TRUE(ITS->CreateTable("Table01", defaultHash));
    EXPECT_FALSE(ITS->CreateTable("Table01", defaultHash));

    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01->GetSize(), 0);
}

TEST_F(STORAGE_GET_TESTS, Get_non_exist_node) {
    auto table01 = ITS->GetTable("Table01");
    EXPECT_EQ(table01, nullptr);
}
