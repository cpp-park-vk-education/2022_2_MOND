// Copyright 2022 mora

#ifndef DBCORE_ITABLESTORAGE_H
#define DBCORE_ITABLESTORAGE_H

#include "IHashTable.h"

#include <iostream>

class ITableStorage {
public:
    virtual bool CreateTable(const std::string&, const size_t (*h)(size_t)) = 0;

    virtual bool CreateTable(const std::string&) = 0;

    virtual bool DeleteTable(const std::string&) = 0;

    virtual IHashTable* GetTable(const std::string&) const = 0;

    virtual size_t GetNumTables() const = 0;

    virtual std::vector<std::string> ShowTables() const = 0;

    virtual ~ITableStorage() {}
};


#endif // DBCORE_ITABLESTORAGE_H
