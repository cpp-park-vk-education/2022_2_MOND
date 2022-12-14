// Copyright 2022 mora

#ifndef DBCORE_TABLESTORAGE_H
#define DBCORE_TABLESTORAGE_H

#include "ITableStorage.h"

class TableStorage : public ITableStorage {
   public:
    TableStorage();

    explicit TableStorage(const size_t& tableSize);
    bool CreateTable(
        const std::string&,
        const std::function<size_t(const std::vector<uint8_t>&)>&) override;
    bool CreateTable(const std::string&) override;
    bool DeleteTable(const std::string&) const override;
    [[nodiscard]] IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*
    GetTable(const std::string&) const override;
    [[nodiscard]] size_t GetNumTables() const override;
    [[nodiscard]] std::vector<std::string> GetTableNames() const override;
    ~TableStorage() override;

   private:
    void clear() const;
    IHashTable<std::string,
               IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*>*
        _tableStorage = nullptr;
};

TableStorage::TableStorage() {
    _tableStorage = new QuadraticProbingTable<
        std::string, IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*>(
        stringHash);
}

TableStorage::TableStorage(const size_t& tableSize) {
    _tableStorage = new QuadraticProbingTable<
        std::string, IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*>(
        tableSize, stringHash);
}

bool TableStorage::CreateTable(
    const std::string& tableName,
    const std::function<size_t(const std::vector<uint8_t>&)>& hash) {
    auto table =
        new QuadraticProbingTable<std::vector<uint8_t>, std::vector<uint8_t>>(
            hash);

    auto result = _tableStorage->Insert(tableName, table);

    if(!result){
        delete table;
    }

    return result;
}

bool TableStorage::CreateTable(const std::string& tableName) {
    auto table =
        new QuadraticProbingTable<std::vector<uint8_t>, std::vector<uint8_t>>(
            defaultHash);

    auto result = _tableStorage->Insert(tableName, table);

    if(!result){
        delete table;
    }

    return result;
}

bool TableStorage::DeleteTable(const std::string& tableName) const {
    auto table = _tableStorage->Get(tableName);
    auto result =  _tableStorage->Remove(tableName);

    delete table;
    return result;
}

IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* TableStorage::GetTable(
    const std::string& tableName) const {
    return _tableStorage->Get(tableName);
}

size_t TableStorage::GetNumTables() const { return _tableStorage->GetSize(); }

std::vector<std::string> TableStorage::GetTableNames() const {
    return _tableStorage->GetKeys();
}

TableStorage::~TableStorage() {
    clear();
    delete _tableStorage;
}
void TableStorage::clear() const {
    auto keys = GetTableNames();
    for(auto &it: keys){
        DeleteTable(it);
    }
}

#endif  // DBCORE_TABLESTORAGE_H
