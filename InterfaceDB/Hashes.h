// Copyright 2022 mora

#ifndef INTERFACEDB_HASHES_H
#define INTERFACEDB_HASHES_H
#include <iostream>

template<typename Key>
class [[maybe_unused]] defaultHash {
public:
    size_t operator() (const Key key) const{
        return static_cast<size_t> (std::hash<size_t>{}(key));
    }
};
#endif //INTERFACEDB_HASHES_H
