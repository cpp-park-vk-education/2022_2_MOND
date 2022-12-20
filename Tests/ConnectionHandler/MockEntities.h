//
// Created by ogrebatel on 11.12.22.
//

#ifndef MOND_DB_MOCKENTITIES_H
#define MOND_DB_MOCKENTITIES_H

#include <gmock/gmock.h>

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
};


class MockStorage: public ITableStorage {
public:
    ~MockStorage() override = default;
    MOCK_METHOD(bool, CreateTable, (const std::string&, const std::function<size_t(const std::vector<uint8_t>&)>& hash), (override));
    MOCK_METHOD(bool, CreateTable, (const std::string&), (override));
    MOCK_METHOD(bool, DeleteTable, (const std::string&), (override));
    MOCK_METHOD((IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*), GetTable, (const std::string&), (const, override));
    MOCK_METHOD(size_t, GetNumTables, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, GetTableNames, (), (const, override));
};

using ::testing::Return;

#endif //MOND_DB_MOCKENTITIES_H
