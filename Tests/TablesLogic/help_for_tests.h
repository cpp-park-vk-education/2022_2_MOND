// Copyright 2022 mora

#pragma once

#include "IHashTable.h"
#include "QuadraticProbingTable.h"
//#include "ITableStorage.h"

#include <gtest/gtest.h>

size_t hash(const uint8_t* key, const size_t &key_len){
    size_t hash = 0;
    for (size_t i = 0; i < key_len; ++i) {
        hash = (hash * 13 + key[i]);
    }
    return hash;
}
