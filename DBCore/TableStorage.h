// Copyright 2022 mora

#ifndef DBCORE_TABLESTORAGE_H
#define DBCORE_TABLESTORAGE_H

#include "ITableStorage.h"

class TableStorage : public ITableStorage {
   public:
    TableStorage();

    explicit TableStorage(const size_t& tableSize);
    bool CreateTable(const std::vector<uint8_t>& value,
                     const std::function<size_t(const std::vector<uint8_t>&)>&
                         hash) override;
    bool CreateTable(const std::vector<uint8_t>& value) override;
    bool DeleteTable(const std::vector<uint8_t>&) override;
    [[nodiscard]] std::vector<uint8_t> GetTable(const std::vector<uint8_t>&) const override;
    [[nodiscard]] size_t GetNumTables() const override;
    [[nodiscard]] std::vector<std::vector<uint8_t>> ShowTables() const override;
    ~TableStorage() override;

   private:
    IHashTable* _tableStorage = nullptr;
};

TableStorage::TableStorage() {
    _tableStorage = new QuadraticProbingTable(defaultHash);
}

TableStorage::TableStorage(const size_t& tableSize) {
    _tableStorage = new QuadraticProbingTable(tableSize, defaultHash);
}

bool TableStorage::CreateTable(
    const std::vector<uint8_t>& tableName,
    const std::function<size_t(const std::vector<uint8_t>&)>& hash) {
    IHashTable* table = new QuadraticProbingTable(hash);

    return _tableStorage->Insert(tableName, table);
}

bool TableStorage::CreateTable(const std::vector<uint8_t>& tableName) {
    IHashTable* table = new QuadraticProbingTable(defaultHash);

    return _tableStorage->Insert(tableName, table);
}

bool TableStorage::DeleteTable(const std::vector<uint8_t>& tableName) {
    return _tableStorage->Remove(tableName);
}

std::vector<uint8_t> TableStorage::GetTable(const std::vector<uint8_t>& tableName) const {
        return _tableStorage->Get(tableName);
}

size_t TableStorage::GetNumTables() const { return _tableStorage->GetSize(); }

std::vector<std::vector<uint8_t>> TableStorage::ShowTables() const {
    return std::vector<std::vector<uint8_t>>();
}

TableStorage::~TableStorage() { delete _tableStorage; }

#endif  // DBCORE_TABLESTORAGE_H
