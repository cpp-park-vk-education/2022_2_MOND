// Copyright 2022 mora

#pragma once

#include "Hashes.h"

#include <iostream>
#include <vector>

template <typename Key, typename Value>
class IHashTable {
public:
    [[nodiscard]] virtual bool Insert(const Key &key,
                                      const Value &value) = 0;
    [[nodiscard]] virtual bool Remove(const Key &key) = 0;
    [[nodiscard]] virtual bool Find(const Key &key) const = 0;
    [[nodiscard]] virtual bool Clear() = 0;
    [[nodiscard]] virtual size_t GetSize() const = 0;
    [[nodiscard]] virtual Value Get(const Key &key) const = 0;
    [[nodiscard]] virtual bool Update(const Key &key,
                                      const Value &value) = 0;
    [[nodiscard]] virtual std::vector<Key> GetKeys() = 0;
    virtual ~IHashTable() = default;

private:
    virtual void grow() = 0;
};
