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
    MOCK_METHOD(bool, CreateTable, (const std::string&, const std::function<size_t(const std::vector<uint8_t>&)>& hash), (override));
    MOCK_METHOD(bool, CreateTable, (const std::string&), (override));
    MOCK_METHOD(bool, DeleteTable, (const std::string&), (const, override));
    MOCK_METHOD((IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*), GetTable, (const std::string&), (const, override));
    MOCK_METHOD(size_t, GetNumTables, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, GetTableNames, (), (const, override));
};

class CheckingWorkersForIStorageUsage : public testing::Test{
public:
    Request request;
    IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* table = nullptr;
    MockStorage storage;
    workerFactory factory;
};

TEST_F(CheckingWorkersForIStorageUsage, CreateTableWorker) {
    request._type = requestType::CREATE_TABLE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, CreateTable(request._table_name)).Times(1);
    worker->operate();
    delete worker;
}

//TEST_F(CheckingWorkersForITableUsage, CreateTableWithHash) {
//    _request._type = requestType::INSERT;
//    auto worker = factory.get(_request, _storage, &table);
//    EXPECT_CALL(table, Insert).Times(1);
//    worker->operate();
//    delete worker;
//}

TEST_F(CheckingWorkersForIStorageUsage, DeleteTableWorker) {
    request._type = requestType::DELETE_TABLE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, DeleteTable(request._table_name)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, GetTableWorker) {
    request._type = requestType::GET_TABLE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request._table_name)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, GetNumTablesWorker) {
    request._type = requestType::GET_NUM_TABLES;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetNumTables).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, ShowTablesWorker) {
    request._type = requestType::SHOW_TABLES;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetNumTables).Times(1);
    worker->operate();
    delete worker;
}

#endif //MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H
