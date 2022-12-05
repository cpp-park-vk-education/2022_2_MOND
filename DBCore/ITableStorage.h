// Copyright 2022 mora

#ifndef DBCORE_ITABLESTORAGE_H
#define DBCORE_ITABLESTORAGE_H

#include <functional>
#include <iostream>

#include "IHashTable.h"

class ITableStorage {
   public:
    virtual bool CreateTable(
        const std::string&,
        const std::function<size_t(const std::vector<uint8_t>&)>& hash) = 0;
    virtual bool CreateTable(const std::string&) = 0;
    virtual bool DeleteTable(const std::string&) const = 0;
    virtual IHashTable<std::vector<uint8_t>, std::vector<uint8_t>>* GetTable(
        const std::string&) const = 0;
    virtual size_t GetNumTables() const = 0;
    virtual std::vector<std::string> GetTableNames() const = 0;
    virtual ~ITableStorage() = default;
};

#endif  // DBCORE_ITABLESTORAGE_H
