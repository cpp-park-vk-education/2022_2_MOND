// Copyright 2022 mora

#ifndef DBCORE_HASHES_H_
#define DBCORE_HASHES_H_
#include <iostream>
#include <string>
#include <vector>

size_t defaultHash(const std::vector<uint8_t> &key) {
    size_t hash = 0;
    for (auto &i : key) {
        hash = (hash * 13 + i);
    }
    return hash;
}

size_t stringHash(const std::string &key) {
    size_t hash = 0;
    const char *str = key.c_str();
    for (; *str != 0; ++str) {
        hash = (hash * 13 + static_cast<size_t>(*str));
    }
    return hash;
}

#endif  // DBCORE_HASHES_H_
