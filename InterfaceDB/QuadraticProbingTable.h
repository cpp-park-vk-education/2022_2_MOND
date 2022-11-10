// Copyright 2022 mora

#pragma once

#include "IHashTable.h"
#include "HTAllocator.h"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>


template<typename Key, typename Value, class Hash = defaultHash<Key>>
class QuadraticProbingTable : public IHashTable<Key, Value, Hash> {
    const static uint32_t FREE = 0;
    const static uint32_t BUSY = 1;
    const static uint32_t REMOVED = 2;

    Hash HashFunc = Hash();

    struct HashNode {
        Key key;
        Value value;
        int state = FREE;
    };

    size_t _size;

    std::vector<HashNode, NAlloc<HashNode>> _cells;

public:

    QuadraticProbingTable(const uint32_t tableSize);

    QuadraticProbingTable(const QuadraticProbingTable &table);

    bool Insert(const Key &key, const Value &value);

    bool Remove(const Key &key);

    bool Find(const Key &key) const;

    bool Clear();

    size_t GetSize() const;

    Value Get(const Key &key) const;

    std::vector<Value> GetBusyNodes() const;

    void ChangeValue(const Key &key, const Value &value);

    bool PrintToFile(const std::string &path, size_t sizeOfNode) const;

    char *ReadFromFile(const std::string &path, size_t *outsize) const;

    ~QuadraticProbingTable();
};


template<typename Key, typename Value, class Hash>
QuadraticProbingTable<Key, Value, Hash>::QuadraticProbingTable(const uint32_t tableSize) : _size(0) {
    _cells.reserve(tableSize);
    _cells.resize(tableSize);
}

template<typename Key, typename Value, class Hash>
QuadraticProbingTable<Key, Value, Hash>::QuadraticProbingTable(const QuadraticProbingTable &table) : _size(table._size) {
    *this = table;
}

template<typename Key, typename Value, class Hash>
bool QuadraticProbingTable<Key, Value, Hash>::Insert(const Key &key, const Value &value) {
    size_t sequenceLength = 0;
    size_t hash = HashFunc(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state != BUSY) {
            _cells[index].key = key;
            _cells[index].value = value;
            _cells[index].state = BUSY;

            _size++;

            return true;
        }
        sequenceLength++;
    }
    return false;
}

template<typename Key, typename Value, class Hash>
bool QuadraticProbingTable<Key, Value, Hash>::Remove(const Key &key) {
    size_t sequenceLength = 0;
    auto hash = HashFunc(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state == BUSY && _cells[index].key == key) {
            _cells[index].state = REMOVED;

            _size--;

            return true;
        }

        if (_cells[index].state == FREE) {
            return false;
        }
        sequenceLength++;
    }

    return false;
}

template<typename Key, typename Value, class Hash>
bool QuadraticProbingTable<Key, Value, Hash>::Find(const Key &key) const {
    size_t sequenceLength = 0;
    auto hash = HashFunc(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state == BUSY && _cells[index].key == key) {
            return true;
        }

        if (_cells[index].state == FREE) {
            return false;
        }
        sequenceLength++;
    }
    return false;
}

template<typename Key, typename Value, class Hash>
bool QuadraticProbingTable<Key, Value, Hash>::Clear() {
    _cells.clear();

    _size = 0;

    _cells.resize(_cells.capacity());

    for (auto i = 0; i < _cells.capacity(); i++) {
        _cells[i].state = FREE;
    }

    return true;
}

template<typename Key, typename Value, class Hash>
size_t QuadraticProbingTable<Key, Value, Hash>::GetSize() const {
    return _size;
}


template<typename Key, typename Value, class Hash>
Value QuadraticProbingTable<Key, Value, Hash>::Get(const Key &key) const {
    size_t sequenceLength = 0;
    auto hash = HashFunc(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state == BUSY && _cells[index].key == key) {
            return _cells[index].value;
        }

        if (_cells[index].state == FREE) {
            throw std::string("No value with this key");
        }
        sequenceLength++;
    }
    throw std::string("No value with this key");
}

template<typename Key, typename Value, class Hash>
QuadraticProbingTable<Key, Value, Hash>::~QuadraticProbingTable() {
    _cells.clear();
}

template<typename Key, typename Value, class Hash>
std::vector<Value> QuadraticProbingTable<Key, Value, Hash>::GetBusyNodes() const {
    std::vector<Value> nodes;

    for (size_t i = 0; i < _cells.capacity(); ++i) {
        if (_cells[i].state != BUSY) {
            continue;
        }
        nodes.emplace_back(_cells[i].value);
    }
    return nodes;
}

template<typename Key, typename Value, class Hash>
void QuadraticProbingTable<Key, Value, Hash>::ChangeValue(const Key &key, const Value &value) {
    size_t sequenceLength = 0;
    auto hash = HashFunc(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state == BUSY && _cells[index].key == key) {
            _cells[index].value = value;
            return;
        }

        if (_cells[index].state == FREE) {
            throw std::string("No value with this key");
        }
        sequenceLength++;
    }

    throw std::string("No value with this key");
}

template<typename Key, typename Value, class Hash>
bool QuadraticProbingTable<Key, Value, Hash>::PrintToFile(const std::string &path, size_t sizeOfNode) const {
    std::ofstream outfile;
    outfile.open(path, std::ios::out | std::ios::binary);
    if (!outfile) return false;

    for (int i = 0; i < _cells.capacity(); i++) {
        if (_cells[i].state != BUSY) {
            continue;
        }
        outfile.write((char *) (&_cells[i].value), sizeOfNode);
    }
    outfile.close();

    return true;
}

template<typename Key, typename Value, class Hash>
char *QuadraticProbingTable<Key, Value, Hash>::ReadFromFile(const std::string &path, size_t *outsize) const {
    std::streampos fileSize;
    std::ifstream infile;
    char *memblock = nullptr;

    infile.open(path, std::ios::in | std::ios::binary | std::ios::ate);

    if (!infile) return memblock;


    fileSize = infile.tellg();
    memblock = new char[fileSize];
    infile.seekg(0, std::ios::beg);
    infile.read(memblock, fileSize);

    infile.close();

    *outsize = fileSize;

    return memblock;
}
