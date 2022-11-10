// Copyright 2022 mora

#ifndef INTERFACEDB_ITABLESTORAGE_H
#define INTERFACEDB_ITABLESTORAGE_H

#include "IHashTable.h"

#include <iostream>

template<typename Key, typename Value>
class ITableStorage {
public:
    virtual void CreateTable(std::string&, size_t (*h)(Key)) = 0;

    virtual void DeleteTable(std::string&) = 0;

    virtual IHashTable<Key, Value>* GetTable(std::string&) const = 0;

    virtual ~ITableStorage() {}
};


#endif //INTERFACEDB_ITABLESTORAGE_H
