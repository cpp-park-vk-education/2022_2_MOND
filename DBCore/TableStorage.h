// Copyright 2022 mora

#ifndef DBCORE_TABLESTORAGE_H
#define DBCORE_TABLESTORAGE_H

#include "ITableStorage.h"

class TableStorage : public ITableStorage {
public:
    TableStorage();

    explicit TableStorage(const uint32_t &tableSize);

    bool CreateTable(const std::string &, std::function<size_t(const uint8_t *, const size_t &)> hash) override;

    bool CreateTable(const std::string &) override;

    bool DeleteTable(const std::string &) override;

    [[nodiscard]] IHashTable *GetTable(const std::string &) const override;

    [[nodiscard]] size_t GetNumTables() const override;

    [[nodiscard]] std::vector<std::string> ShowTables() const override;

    ~TableStorage() override;

private:
    IHashTable *_tableStorage = nullptr;
};

TableStorage::TableStorage() {
    _tableStorage = new QuadraticProbingTable(defaultHash);
}

TableStorage::TableStorage(const uint32_t &tableSize) {
    _tableStorage = new QuadraticProbingTable(tableSize, defaultHash);
}

bool
TableStorage::CreateTable(const std::string &tableName, std::function<size_t(const uint8_t *, const size_t &)> hash) {
    IHashTable *table = new QuadraticProbingTable(hash);

    return _tableStorage->Insert((uint8_t *) tableName.c_str(), tableName.size(),
                                 reinterpret_cast<uint8_t *>(&table), sizeof(uint8_t *));
}

bool TableStorage::CreateTable(const std::string &tableName) {
    IHashTable *table = new QuadraticProbingTable(defaultHash);

    return _tableStorage->Insert((uint8_t *) tableName.c_str(), tableName.size(),
                                 (uint8_t *) &table, sizeof(uint8_t *));
}

bool TableStorage::DeleteTable(const std::string &tableName) {
    return _tableStorage->Remove((uint8_t *) tableName.c_str(), tableName.size());
}

IHashTable *TableStorage::GetTable(const std::string &tableName) const {
    auto result = _tableStorage->Get((uint8_t *) tableName.c_str(), tableName.size());

    return result == nullptr ? nullptr : *(IHashTable **) result;
}

size_t TableStorage::GetNumTables() const {
    return _tableStorage->GetSize();
}

std::vector<std::string> TableStorage::ShowTables() const {
    return std::vector<std::string>();
}

TableStorage::~TableStorage() {
    delete _tableStorage;
}

#endif // DBCORE_TABLESTORAGE_H
