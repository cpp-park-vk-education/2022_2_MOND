// Copyright 2022 mora

#include "help_for_tests.h"
#include "ITableStorage.h"
#include "TableStorage.h"
#include "IHashTable.h"
#include "QuadraticProbingTable.h"
#include "Hashes.h"

class STORAGE_DELETE_TESTS : public testing::Test {
protected:
    void SetUp() override {
        ITS = new TableStorage();
    }

    void TearDown() override{
        delete ITS;
    }

    ITableStorage *ITS = nullptr;
};

TEST_F(STORAGE_DELETE_TESTS, Delete_one_table) {
    ITS->CreateTable("Table01");

    EXPECT_TRUE(ITS->DeleteTable("Table01"));
}

TEST_F(STORAGE_DELETE_TESTS, Delete_one_table_with_hash) {
    ITS->CreateTable("Table01", defaultHash);

    EXPECT_TRUE(ITS->DeleteTable("Table01"));
}

TEST_F(STORAGE_DELETE_TESTS, Delete_before_grow_nodes) {
    ITS->CreateTable("Table01");
    ITS->CreateTable("Table02");
    ITS->CreateTable("Table03");
    ITS->CreateTable("Table04");
    ITS->CreateTable("Table05");
    ITS->CreateTable("Table06");

    EXPECT_TRUE(ITS->DeleteTable("Table01"));
    EXPECT_TRUE(ITS->DeleteTable("Table02"));
    EXPECT_TRUE(ITS->DeleteTable("Table03"));
    EXPECT_TRUE(ITS->DeleteTable("Table04"));
    EXPECT_TRUE(ITS->DeleteTable("Table05"));
    EXPECT_TRUE(ITS->DeleteTable("Table06"));
}

TEST_F(STORAGE_DELETE_TESTS, Delete_after_grow_nodes) {
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

    EXPECT_TRUE(ITS->DeleteTable("Table01"));
    EXPECT_TRUE(ITS->DeleteTable("Table02"));
    EXPECT_TRUE(ITS->DeleteTable("Table03"));
    EXPECT_TRUE(ITS->DeleteTable("Table04"));
    EXPECT_TRUE(ITS->DeleteTable("Table05"));
    EXPECT_TRUE(ITS->DeleteTable("Table06"));
    EXPECT_TRUE(ITS->DeleteTable("Table07"));
    EXPECT_TRUE(ITS->DeleteTable("Table08"));
    EXPECT_TRUE(ITS->DeleteTable("Table09"));
    EXPECT_TRUE(ITS->DeleteTable("Table10"));
}

TEST_F(STORAGE_DELETE_TESTS, Delete_same_nodes) {
    ITS->CreateTable("Table01");
    ITS->CreateTable("Table01");

    EXPECT_TRUE(ITS->DeleteTable("Table01"));
    EXPECT_FALSE(ITS->DeleteTable("Table01"));
}
