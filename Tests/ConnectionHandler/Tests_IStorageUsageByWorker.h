//
// Created by ogrebatel on 04.12.22.
//

#ifndef MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H
#define MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H

#include "IWorker.h"
#include "MockEntities.h"

class CheckingWorkersForIStorageUsage : public testing::Test{

protected:
    void SetUp() override {
        request->_table_name = "MyFirstTable";
        ON_CALL(storage, GetTable("MyFirstTable")).WillByDefault(Return(&table));
        ON_CALL(storage, GetTable("NewTable")).WillByDefault(Return(nullptr));
    }

public:
    std::shared_ptr<Request> request;
    MockStorage storage;
    MockTable table;
    workerFactory factory;
};

TEST_F(CheckingWorkersForIStorageUsage, CreateTableWorker) {

    request->_type = RequestType::CREATE_TABLE;
    request->_table_name = "NewTable";
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(storage, CreateTable(request->_table_name)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, DeleteTableWorker) {
    request->_type = RequestType::DELETE_TABLE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, DeleteTable(request->_table_name)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, GetTableWorker) {
    request->_type = RequestType::GET_TABLE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForIStorageUsage, GetNumTablesWorker) {
    request->_type = RequestType::GET_NUM_TABLES;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetNumTables).Times(1);
    worker->operate();
    delete worker;
}

#endif //MOND_DB_TESTS_ISTORAGEUSAGEBYWORKER_H
