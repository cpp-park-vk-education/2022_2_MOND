// Copyright 2022 mora

#pragma once

#include "Hashes.h"

#include <iostream>
#include <vector>

template<typename Key, typename Value, class Hash = defaultHash<Key>>
class IHashTable {
public:
    virtual bool Insert(const Key &key, const Value &value) = 0;

    virtual bool Remove(const Key &key) = 0;

    virtual bool Find(const Key &key) const = 0;

    virtual bool Clear() = 0;

    [[nodiscard]] virtual size_t GetSize() const = 0;

    virtual Value Get(const Key &key) const = 0;

    virtual std::vector<Value> GetBusyNodes() const = 0;

    virtual void ChangeValue(const Key &key, const Value &value) = 0;

    [[nodiscard]] virtual bool PrintToFile(const std::string &path, size_t sizeOfNode) const = 0;

    virtual char *ReadFromFile(const std::string &path, size_t *outsize) const = 0;

    virtual ~IHashTable() = default;
};
