// Copyright 2022 mora

#ifndef TMP_2022_2_MOND_DBCORE_HASHES_H
#define TMP_2022_2_MOND_DBCORE_HASHES_H
#include <iostream>

size_t defaultHash(const uint8_t* key, const size_t &key_len){
    size_t hash = 0;
    for (size_t i = 0; i < key_len; ++i) {
        hash = (hash * 13 + key[i]);
    }
    return hash;
}

#endif // TMP_2022_2_MOND_DBCORE_HASHES_H
