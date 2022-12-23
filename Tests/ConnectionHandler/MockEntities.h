//
// Created by ogrebatel on 11.12.22.
//

#ifndef MOND_DB_MOCKENTITIES_H
#define MOND_DB_MOCKENTITIES_H

#include <gmock/gmock.h>

class MockTable: public IHashTable<std::string, std::string> {
public:
~MockTable() override = default;
MOCK_METHOD(bool, Insert, (const std::string &, const std::string &), (override));
MOCK_METHOD(bool, Remove, (const std::string &), (override));
MOCK_METHOD(bool, Find, (const std::string &), (const, override));
MOCK_METHOD(bool, Clear, (), (override));
MOCK_METHOD(size_t, GetSize, (), (const, override));
MOCK_METHOD(std::string, Get, (const std::string &key), (const, override));
MOCK_METHOD(bool, Update, (const std::string &, const std::string &), (override));
MOCK_METHOD(std::vector<std::string>, GetKeys, (), (override));
};


class MockStorage: public ITableStorage {
public:
    ~MockStorage() override = default;
    MOCK_METHOD(bool, CreateTable, (const std::string&, const std::function<size_t(const std::string&)>& hash), (override));
    MOCK_METHOD(bool, CreateTable, (const std::string&), (override));
    MOCK_METHOD(bool, DeleteTable, (const std::string&), (override));
    MOCK_METHOD((IHashTable<std::string, std::string>*), GetTable, (const std::string&), (const, override));
    MOCK_METHOD(size_t, GetNumTables, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, GetTableNames, (), (const, override));
};

using ::testing::Return;

#endif //MOND_DB_MOCKENTITIES_H
