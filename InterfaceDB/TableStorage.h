// Copyright 2022 mora

#ifndef INTERFACEDB_TABLESTORAGE_H
#define INTERFACEDB_TABLESTORAGE_H

#include "ITableStorage.h"

template<typename Key, typename Value>
class TableStorage : public ITableStorage<Key, Value> {
private:
    IHashTable<std::string, IHashTable<Key, Value>> *_tableStorage;

public:
    void CreateTable(std::string&, size_t (*h)(Key));

    void DeleteTable(std::string&);

    IHashTable<Key, Value>* GetTable(std::string&);

    ~TableStorage();
};


#endif //INTERFACEDB_TABLESTORAGE_H
