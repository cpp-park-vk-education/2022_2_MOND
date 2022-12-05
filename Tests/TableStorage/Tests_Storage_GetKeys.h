// Copyright 2022 mora

#include "help_for_tests.h"
#include "ITableStorage.h"
#include "TableStorage.h"
#include "IHashTable.h"
#include "QuadraticProbingTable.h"
#include "Hashes.h"

class STORAGE_GET_KEYS_TESTS : public testing::Test {
   protected:
    void SetUp() override {
        ITS = new TableStorage();
    }

    void TearDown() override{
        delete ITS;
    }

    ITableStorage *ITS = nullptr;
};

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_one_table) {
    ITS->CreateTable("Table01");

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 1);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_one_table_with_hash) {
    ITS->CreateTable("Table01", defaultHash);

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 1);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_before_grow_nodes) {
    ITS->CreateTable("Table01");
    ITS->CreateTable("Table02");
    ITS->CreateTable("Table03");
    ITS->CreateTable("Table04");
    ITS->CreateTable("Table05");
    ITS->CreateTable("Table06");

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 6);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_before_grow_nodes_with_hash) {
    ITS->CreateTable("Table01", defaultHash);
    ITS->CreateTable("Table02", defaultHash);
    ITS->CreateTable("Table03", defaultHash);
    ITS->CreateTable("Table04", defaultHash);
    ITS->CreateTable("Table05", defaultHash);
    ITS->CreateTable("Table06", defaultHash);

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 6);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_after_grow_nodes) {
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

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 10);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_after_grow_nodes_with_hash) {
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

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 10);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_same_nodes) {
    ITS->CreateTable("Table01");
    ITS->CreateTable("Table01");

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 1);
}

TEST_F(STORAGE_GET_KEYS_TESTS, Get_Keys_same_nodes_with_hash) {
    ITS->CreateTable("Table01", defaultHash);
    ITS->CreateTable("Table01", defaultHash);

    auto vec = ITS->GetTableNames();

    for (auto& it: vec) {
        std::cout << it << std::endl;
    }

    EXPECT_EQ(vec.size(), 1);
}
