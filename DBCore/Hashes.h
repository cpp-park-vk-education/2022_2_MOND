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

#endif // TMP_2022_2_MOND_DBCORE_HASHES_H
