// Copyright 2022 mora

#ifndef DBCORE_HASHES_H
#define DBCORE_HASHES_H
#include <iostream>

size_t GetHash(size_t id) {
    return static_cast<size_t> (std::hash<size_t>{}(id));
}

#endif // DBCORE_HASHES_H
