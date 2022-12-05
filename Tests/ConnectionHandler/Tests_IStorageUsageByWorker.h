//
// Created by ogrebatel on 04.12.22.
//

#ifndef MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H
#define MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H

#include <gmock/gmock.h>
#include "IWorker.h"


class MockStorage: public ITableStorage {
public:
    ~MockStorage() override = default;
    MOCK_METHOD(bool, CreateTable, (const std::vector<uint8_t>&,const std::function<size_t(const std::vector<uint8_t>&)>& hash), (override));
    MOCK_METHOD(bool, CreateTable, (const std::vector<uint8_t>&), (override));
    MOCK_METHOD(bool, DeleteTable, (const std::vector<uint8_t>&), (override));
    MOCK_METHOD(std::vector<uint8_t>, GetTable, (const std::vector<uint8_t>&), (const, override));
    MOCK_METHOD(size_t, GetNumTables, (), (const, override));
    MOCK_METHOD(std::vector<std::vector<uint8_t>>, ShowTables, (), (const, override));
};

class CheckingWorkersForIStorageUsage : public testing::Test{
public:
    Request request;
    IHashTable* table = nullptr;
    MockStorage storage;
    workerFactory factory;
};

TEST_F(CheckingWorkersForIStorageUsage, CreateTableWorker) {
    request.type = requestType::CREATE_TABLE;
    auto worker = factory.get(request, &storage, table);
    EXPECT_CALL(storage, CreateTable(request.key)).Times(1);
    worker->operate();
    delete worker;
}

//TEST_F(CheckingWorkersForITableUsage, CreateTableWithHash) {
//    request.type = requestType::INSERT;
//    auto worker = factory.get(request, storage, &table);
//    EXPECT_CALL(table, Insert).Times(1);
//    worker->operate();
//    delete worker;
//}

TEST_F(CheckingWorkersForIStorageUsage, DeleteTableWorker) {
    request.type = requestType::DELETE_TABLE;
    auto worker = factory.get(request, &storage, table);
    EXPECT_CALL(storage, DeleteTable(request.key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, GetTableWorker) {
    request.type = requestType::GET_TABLE;
    auto worker = factory.get(request, &storage, table);
    EXPECT_CALL(storage, GetTable(request.key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, GetNumTablesWorker) {
    request.type = requestType::GET_NUM_TABLES;
    auto worker = factory.get(request, &storage, table);
    EXPECT_CALL(storage, GetNumTables).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, ShowTablesWorker) {
    request.type = requestType::SHOW_TABLES;
    auto worker = factory.get(request, &storage, table);
    EXPECT_CALL(storage, ShowTables).Times(1);
    worker->operate();
    delete worker;
}

#endif //MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H
