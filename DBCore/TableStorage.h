// Copyright 2022 mora

#ifndef DBCORE_TABLESTORAGE_H
#define DBCORE_TABLESTORAGE_H

#include "ITableStorage.h"

class TableStorage : public ITableStorage {
public:
    TableStorage();
    TableStorage(const uint32_t &tableSize);

    bool CreateTable(const std::string &, std::function<size_t(const uint8_t *, const size_t &)> hash);
    bool CreateTable(const std::string &);
    bool DeleteTable(const std::string &);
    IHashTable* GetTable(const std::string &) const;
    size_t GetNumTables() const;
    std::vector <std::string> ShowTables() const;

    ~TableStorage();

private:
    IHashTable *_tableStorage = nullptr;
};


#endif // DBCORE_TABLESTORAGE_H
