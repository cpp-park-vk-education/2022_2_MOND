// Copyright 2022 mora

#pragma once

#include "Hashes.h"

#include <iostream>
#include <vector>

class IHashTable {
public:
    virtual bool Insert(uint8_t *key,
                        const size_t &key_len,
                        uint8_t *value,
                        const size_t &value_len) = 0;

    virtual bool Remove(const uint8_t *key,
                        const size_t &key_len) = 0;

    virtual bool Find(const uint8_t *key,
                      const size_t &key_len) const = 0;

    virtual bool Clear() = 0;

    [[nodiscard]] virtual size_t GetSize() const = 0;

    virtual uint8_t *Get(const uint8_t *key,
                         const size_t &key_len) const = 0;

    virtual bool Update(uint8_t *key,
                        const size_t &key_len,
                        uint8_t *value,
                        const size_t &value_len) = 0;

    virtual ~IHashTable() = default;

private:
    virtual void grow() = 0;
};
