// Copyright 2022 mora

#ifndef DBCORE_TABLESTORAGE_H
#define DBCORE_TABLESTORAGE_H

#include "ITableStorage.h"

class TableStorage : public ITableStorage {
private:
    IHashTable *_tableStorage;

public:
    TableStorage(const uint32_t &tableSize);

    bool CreateTable(const std::string &, const size_t (*h)(size_t));

    bool CreateTable(const std::string &);

    bool DeleteTable(const std::string &);

    IHashTable* GetTable(const std::string &) const;

    size_t GetNumTables() const;

    std::vector <std::string> ShowTables() const;

    ~TableStorage();
};


#endif // DBCORE_TABLESTORAGE_H
