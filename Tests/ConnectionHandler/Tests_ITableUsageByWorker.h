//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_TESTS_ITABLEUSAGEBYWORKER_H
#define MOND_DB_TESTS_ITABLEUSAGEBYWORKER_H

#include <gmock/gmock.h>
#include "IWorker.h"
#include "IHashTable.h"

class MockTable: public IHashTable<std::vector<uint8_t>, std::vector<uint8_t>> {
public:
    ~MockTable() override = default;
    MOCK_METHOD(bool, Insert, (const std::vector<uint8_t> &, const std::vector<uint8_t> &), (override));
    MOCK_METHOD(bool, Remove, (const std::vector<uint8_t> &), (override));
    MOCK_METHOD(bool, Find, (const std::vector<uint8_t> &), (const, override));
    MOCK_METHOD(bool, Clear, (), (override));
    MOCK_METHOD(size_t, GetSize, (), (const, override));
    MOCK_METHOD(std::vector<uint8_t>, Get, (const std::vector<uint8_t> &key), (const, override));
    MOCK_METHOD(bool, Update, (const std::vector<uint8_t> &, const std::vector<uint8_t> &), (override));
    MOCK_METHOD(std::vector<std::vector<uint8_t>>, GetKeys, (), (override));
private:
    void grow(){}
};

class CheckingWorkersForITableUsage : public testing::Test{
public:
    Request request;
    ITableStorage* storage = nullptr;
    MockTable table;
    workerFactory factory;
};

TEST_F(CheckingWorkersForITableUsage, insertValueWorker) {
    request._type = requestType::INSERT;
    auto worker = factory.get(request, storage);
    EXPECT_CALL(table, Insert(request._key, request._value)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, removeWorker) {
    request._type = requestType::REMOVE;
    auto worker = factory.get(request, storage);
    EXPECT_CALL(table, Remove(request._key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, clearWorker) {
    request._type = requestType::FIND;
    auto worker = factory.get(request, storage);
    EXPECT_CALL(table, Find(request._key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, getSizeWorker) {
    request._type = requestType::GET_SIZE;
    auto worker = factory.get(request, storage);
    EXPECT_CALL(table, GetSize).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, getWorker) {
    request._type = requestType::GET;
    auto worker = factory.get(request, storage);
    EXPECT_CALL(table, Get(request._key)).Times(1);
    worker->operate();
    delete worker;
}

TEST_F(CheckingWorkersForITableUsage, updateWorker) {
    request._type = requestType::UPDATE;
    auto worker = factory.get(request, storage);
    EXPECT_CALL(table, Update(request._key, request._value)).Times(1);
    worker->operate();
    delete worker;
}


#endif //MOND_DB_TESTS_ITABLEUSAGEBYWORKER_H
