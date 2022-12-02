// Copyright 2022 mora

#ifndef DBCORE_ITABLESTORAGE_H
#define DBCORE_ITABLESTORAGE_H

#include "IHashTable.h"

#include <iostream>
#include <functional>

class ITableStorage {
public:
    virtual bool CreateTable(const std::vector<uint8_t>&,const std::function<size_t(const std::vector<uint8_t>&)>& hash) = 0;
    virtual bool CreateTable(const std::vector<uint8_t>&) = 0;
    virtual bool DeleteTable(const std::vector<uint8_t>&) = 0;
    virtual std::vector<uint8_t> GetTable(const std::vector<uint8_t>&) const = 0;
    virtual size_t GetNumTables() const = 0;
    virtual std::vector<std::vector<uint8_t>> ShowTables() const = 0;
    virtual ~ITableStorage() = default;
};

#endif // DBCORE_ITABLESTORAGE_H
