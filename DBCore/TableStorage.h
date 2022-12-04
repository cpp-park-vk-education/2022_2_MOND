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
    bool DeleteTable(const std::string&) override;
    [[nodiscard]] IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>*
    GetTable(const std::string&) const override;
    [[nodiscard]] size_t GetNumTables() const override;
    [[nodiscard]] std::vector<std::string> ShowTables() const override;
    ~TableStorage() override;

   private:
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

    return _tableStorage->Insert(tableName, table);
}

bool TableStorage::CreateTable(const std::string& tableName) {
    auto table =
        new QuadraticProbingTable<std::vector<uint8_t>, std::vector<uint8_t>>(
            defaultHash);

    return _tableStorage->Insert(tableName, table);
}

bool TableStorage::DeleteTable(const std::string& tableName) {
    return _tableStorage->Remove(tableName);
}

IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* TableStorage::GetTable(
    const std::string& tableName) const {
    return _tableStorage->Get(tableName);
}

size_t TableStorage::GetNumTables() const { return _tableStorage->GetSize(); }

std::vector<std::string> TableStorage::ShowTables() const {
    return _tableStorage->GetKeys();
}

TableStorage::~TableStorage() { delete _tableStorage; }

#endif  // DBCORE_TABLESTORAGE_H
