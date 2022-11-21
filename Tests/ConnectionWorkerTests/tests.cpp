//
// Created by ogrebatel on 21.11.22.
//

#include <gtest/gtest.h>
#include "ConnectionWorker.hpp"
#include "InternalEntities.h"


TEST(WorkerFactoryTests, insertWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::INSERT, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), InsertWorker>));
}

TEST(WorkerFactoryTests, removeWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::REMOVE, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), RemoveWorker>));
}

TEST(WorkerFactoryTests, findWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::FIND, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), FindWorker>));
}

TEST(WorkerFactoryTests, clearWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::CLEAR, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), ClearWorker>));
}

TEST(WorkerFactoryTests, getSizeWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::GET_SIZE, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), GetSizeWorker>));
}

TEST(WorkerFactoryTests, getWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::GET, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), GetWorker>));
}

TEST(WorkerFactoryTests, updateWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::UPDATE, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), UpdateWorker>));
}

TEST(WorkerFactoryTests, createTableWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::CREATE_TABLE, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), CreateTableWorker>));
}

TEST(WorkerFactoryTests, getTableWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::GET_TABLE, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), GetTableWorker>));
}

TEST(WorkerFactoryTests, deleteTableWorker) {
    auto ioContext = std::make_shared<boost::asio::io_context>();
    IHashTable *hashTable;
    ITableStorage* tableStorage;
    workerFactory factory;
    auto conn = std::make_shared<Connection>(ioContext);
    auto worker = factory.get(requestType::GET, conn);

    EXPECT_TRUE((std::is_same_v<decltype(*worker), DeleteTableWorker>));
}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

