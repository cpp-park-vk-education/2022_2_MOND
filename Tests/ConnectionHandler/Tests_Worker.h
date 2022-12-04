//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_TESTS_WORKER_H
#define MOND_DB_TESTS_WORKER_H

#include <gmock/gmock.h>
#include "IWorker.h"

class MockTable: public IHashTable {
public:
    ~MockTable() override = default;
    MOCK_METHOD(bool, Insert, (const std::vector<uint8_t> &, const std::vector<uint8_t> &), (override));
    MOCK_METHOD(bool, Remove, (const std::vector<uint8_t> &), (override));
    MOCK_METHOD(bool, Find, (const std::vector<uint8_t> &), (const, override));
    MOCK_METHOD(bool, Clear, (), (override));
    MOCK_METHOD(size_t, GetSize, (), (const, override));
    MOCK_METHOD(std::vector<uint8_t>, Get, (const std::vector<uint8_t> &key), (const, override));
    MOCK_METHOD(bool, Update, (const std::vector<uint8_t> &, const std::vector<uint8_t> &), (override));
private:
    void grow(){}
};
TEST(WorkerFactoryTests, insertWorker) {
    auto* ioContext = new boost::asio::io_context;
    Request request;
    ITableStorage* storage;
    MockTable table;
    request.type = requestType::INSERT;
    workerFactory factory;
    auto worker = factory.get(request, storage, &table);
    EXPECT_CALL(table, Insert).Times(1);
    worker->operate();
}
//
//TEST(WorkerFactoryTests, removeWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::REMOVE, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), RemoveWorker>));
//}
//
//TEST(WorkerFactoryTests, findWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::FIND, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), FindWorker>));
//}
//
//TEST(WorkerFactoryTests, clearWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::CLEAR, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), ClearWorker>));
//}
//
//TEST(WorkerFactoryTests, getSizeWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::GET_SIZE, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), GetSizeWorker>));
//}
//
//TEST(WorkerFactoryTests, getWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::GET, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), GetWorker>));
//}
//
//TEST(WorkerFactoryTests, updateWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::UPDATE, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), UpdateWorker>));
//}
//
//TEST(WorkerFactoryTests, createTableWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::CREATE_TABLE, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), CreateTableWorker>));
//}
//
//TEST(WorkerFactoryTests, getTableWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::GET_TABLE, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), GetTableWorker>));
//}
//
//TEST(WorkerFactoryTests, deleteTableWorker) {
//    auto ioContext = std::make_shared<boost::asio::io_context>();
//    IHashTable *hashTable;
//    ITableStorage* tableStorage;
//    workerFactory factory;
//    auto conn = std::make_shared<Connection>(ioContext);
//    auto worker = factory.get(requestType::GET, conn);
//
//    EXPECT_TRUE((std::is_same_v<decltype(*worker), DeleteTableWorker>));
//}

#endif //MOND_DB_TESTS_WORKER_H
