// Copyright 2022 mora

#ifndef TMP_2022_2_MOND_DBCORE_HASHES_H
#define TMP_2022_2_MOND_DBCORE_HASHES_H
#include <iostream>

size_t GetHash(size_t id) {
    return static_cast<size_t> (std::hash<size_t>{}(id));
}

#endif // TMP_2022_2_MOND_DBCORE_HASHES_H
