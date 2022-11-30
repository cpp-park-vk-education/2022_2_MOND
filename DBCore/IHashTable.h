// Copyright 2022 mora

#pragma once

#include "Hashes.h"

#include <iostream>
#include <vector>

class IHashTable {
public:
    [[nodiscard]] virtual bool Insert(const std::vector<uint8_t> &key,
                                      const std::vector<uint8_t> &value) = 0;
    [[nodiscard]] virtual bool Remove(const std::vector<uint8_t> &key) = 0;
    [[nodiscard]] virtual bool Find(const std::vector<uint8_t> &key) const = 0;
    [[nodiscard]] virtual bool Clear() = 0;
    [[nodiscard]] virtual size_t GetSize() const = 0;
    [[nodiscard]] virtual std::vector<uint8_t> Get(const std::vector<uint8_t> &key) const = 0;
    [[nodiscard]] virtual bool Update(const std::vector<uint8_t> &key,
                                      const std::vector<uint8_t> &value) = 0;
    virtual ~IHashTable() = default;

private:
    virtual void grow() = 0;
};
