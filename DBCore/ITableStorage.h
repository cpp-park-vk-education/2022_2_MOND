// Copyright 2022 mora

#ifndef DBCORE_ITABLESTORAGE_H
#define DBCORE_ITABLESTORAGE_H

#include "IHashTable.h"

#include <iostream>
#include <functional>

class ITableStorage {
public:
    virtual bool CreateTable(const std::string&, std::function<size_t(const uint8_t *, const size_t &)> hash) = 0;
    virtual bool CreateTable(const std::string&) = 0;
    virtual bool DeleteTable(const std::string&) = 0;
    virtual IHashTable* GetTable(const std::string&) const = 0;
    virtual size_t GetNumTables() const = 0;
    virtual std::vector<std::string> ShowTables() const = 0;
    virtual ~ITableStorage() = default;
};

#endif // DBCORE_ITABLESTORAGE_H
