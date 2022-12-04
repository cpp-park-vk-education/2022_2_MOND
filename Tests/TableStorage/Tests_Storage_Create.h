// Copyright 2022 mora

#include "help_for_tests.h"
#include "ITableStorage.h"
#include "TableStorage.h"
#include "IHashTable.h"
#include "QuadraticProbingTable.h"
#include "Hashes.h"

class STORAGE_CREATE_TESTS : public testing::Test {
protected:
    void SetUp() override {
        ITS = new TableStorage();
    }

    void TearDown() override{
        delete ITS;
    }

    ITableStorage *ITS = nullptr;
};

TEST_F(STORAGE_CREATE_TESTS, Create_one_table) {
    EXPECT_TRUE(ITS->CreateTable("Table01"));
}

TEST_F(STORAGE_CREATE_TESTS, Create_one_table_with_hash) {
    EXPECT_TRUE(ITS->CreateTable("Table01", defaultHash));
}

TEST_F(STORAGE_CREATE_TESTS, Create_before_grow_nodes) {
    EXPECT_TRUE(ITS->CreateTable("Table01"));
    EXPECT_TRUE(ITS->CreateTable("Table02"));
    EXPECT_TRUE(ITS->CreateTable("Table03"));
    EXPECT_TRUE(ITS->CreateTable("Table04"));
    EXPECT_TRUE(ITS->CreateTable("Table05"));
    EXPECT_TRUE(ITS->CreateTable("Table06"));
}

TEST_F(STORAGE_CREATE_TESTS, Create_before_grow_nodes_with_hash) {
    EXPECT_TRUE(ITS->CreateTable("Table01", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table02", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table03", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table04", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table05", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table06", defaultHash));
}

TEST_F(STORAGE_CREATE_TESTS, Create_after_grow_nodes) {
    EXPECT_TRUE(ITS->CreateTable("Table01"));
    EXPECT_TRUE(ITS->CreateTable("Table02"));
    EXPECT_TRUE(ITS->CreateTable("Table03"));
    EXPECT_TRUE(ITS->CreateTable("Table04"));
    EXPECT_TRUE(ITS->CreateTable("Table05"));
    EXPECT_TRUE(ITS->CreateTable("Table06"));
    EXPECT_TRUE(ITS->CreateTable("Table07"));
    EXPECT_TRUE(ITS->CreateTable("Table08"));
    EXPECT_TRUE(ITS->CreateTable("Table09"));
    EXPECT_TRUE(ITS->CreateTable("Table10"));
}

TEST_F(STORAGE_CREATE_TESTS, Create_after_grow_nodes_with_hash) {
    EXPECT_TRUE(ITS->CreateTable("Table01", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table02", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table03", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table04", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table05", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table06", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table07", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table08", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table09", defaultHash));
    EXPECT_TRUE(ITS->CreateTable("Table10", defaultHash));
}

TEST_F(STORAGE_CREATE_TESTS, Create_same_nodes) {
    EXPECT_TRUE(ITS->CreateTable("Table01"));
    EXPECT_FALSE(ITS->CreateTable("Table01"));
}

TEST_F(STORAGE_CREATE_TESTS, Create_same_nodes_with_hash) {
    EXPECT_TRUE(ITS->CreateTable("Table01", defaultHash));
    EXPECT_FALSE(ITS->CreateTable("Table01", defaultHash));
}
