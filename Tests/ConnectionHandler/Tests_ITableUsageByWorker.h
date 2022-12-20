//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_TESTS_ITABLEUSAGEBYWORKER_H
#define MOND_DB_TESTS_ITABLEUSAGEBYWORKER_H

#include "IWorker.h"
#include "IHashTable.h"
#include "MockEntities.h"

class CheckingWorkersForITableUsage : public testing::Test{

    void SetUp() override {
        request->_table_name = "MyFirstTable";
        ON_CALL(storage, GetTable("MyFirstTable")).WillByDefault(Return(&table));
    }

public:
    std::shared_ptr<Request> request = std::make_shared<Request>();
    Request answer;
    MockStorage storage;
    MockTable table;
    workerFactory factory;
};

TEST_F(CheckingWorkersForITableUsage, insertValueWorker) {
    request->_type = RequestType::INSERT;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(table, Insert(request->_key, request->_value)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, removeWorker) {
    request->_type = RequestType::REMOVE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(table, Remove(request->_key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, clearWorker) {
    request->_type = RequestType::FIND;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(table, Find(request->_key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, getSizeWorker) {
    request->_type = RequestType::GET_SIZE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(table, GetSize).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, getWorker) {
    request->_type = RequestType::GET;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(table, Get(request->_key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, updateWorker) {
    request->_type = RequestType::UPDATE;
    auto worker = factory.get(request, &storage);
    EXPECT_CALL(storage, GetTable(request->_table_name)).Times(1);
    EXPECT_CALL(table, Update(request->_key, request->_value)).Times(1);
    worker->operate();
    delete worker;
}


#endif //MOND_DB_TESTS_ITABLEUSAGEBYWORKER_H
