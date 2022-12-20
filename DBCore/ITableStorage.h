// Copyright 2022 mora

#ifndef DBCORE_ITABLESTORAGE_H
#define DBCORE_ITABLESTORAGE_H

#include "IHashTable.h"

#include <functional>
#include <iostream>

class ITableStorage {
   public:
    virtual bool CreateTable(
        const std::string&,
        const std::function<size_t(const std::string&)>& hash) = 0;
    virtual bool CreateTable(const std::string&) = 0;
    virtual bool DeleteTable(const std::string&) = 0;
    [[nodiscard]] virtual IHashTable<std::string, std::string>* GetTable(
        const std::string&) const = 0;
    [[nodiscard]] virtual size_t GetNumTables() const = 0;
    [[nodiscard]] virtual std::vector<std::string> GetTableNames() const = 0;
    virtual ~ITableStorage() = default;
};

#endif  // DBCORE_ITABLESTORAGE_H
