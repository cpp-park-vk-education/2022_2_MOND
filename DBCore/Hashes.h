// Copyright 2022 mora

#ifndef TMP_2022_2_MOND_DBCORE_HASHES_H
#define TMP_2022_2_MOND_DBCORE_HASHES_H
#include <iostream>
#include <vector>

size_t defaultHash(const std::vector<uint8_t> &key){
    size_t hash = 0;
    for (auto &i : key) {
        hash = (hash * 13 + i);
    }
    return hash;
}

size_t stringHash(const std::string &key){
    size_t hash = 0;
    const char *str = key.c_str();
    for (; *str != 0; ++str) {
        hash = (hash * 13 + static_cast<unsigned long>(*str));
    }
    return hash;
}

#endif // TMP_2022_2_MOND_DBCORE_HASHES_H
