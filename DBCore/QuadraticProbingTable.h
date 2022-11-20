// Copyright 2022 mora

#pragma once

#include "IHashTable.h"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>


class QuadraticProbingTable : public IHashTable {
    const static uint32_t FREE = 0;
    const static uint32_t BUSY = 1;
    const static uint32_t REMOVED = 2;

    struct HashNode {
        size_t key_len;
        size_t value_len;
        uint32_t state = FREE;
        uint8_t *key;
        uint8_t *value;
    };

    size_t _size;

    std::vector<HashNode> _cells;

    std::function<void(size_t)> _hash;

public:

    QuadraticProbingTable(const uint32_t &tableSize, const std::function<void(size_t)> &func);

    QuadraticProbingTable(const QuadraticProbingTable &table);

    bool Insert(const uint8_t *key,
                const size_t &key_len,
                const uint8_t *value,
                const size_t &value_len);

    bool Remove(const uint8_t *key,
                const size_t &key_len);

    bool Find(const uint8_t *key,
              const size_t &key_len) const;

    bool Clear();

    size_t GetSize() const;

    uint8_t *Get(const uint8_t *key,
                 const size_t &key_len) const;

    bool Update(const uint8_t *key,
                const size_t &key_len,
                const uint8_t *value,
                const size_t &value_len);

    ~QuadraticProbingTable();
};


QuadraticProbingTable::QuadraticProbingTable(const uint32_t &tableSize, const std::function<void(size_t)> &hash)
        : _size(0), _hash(hash) {
    _cells.reserve(tableSize);
    _cells.resize(tableSize);
}

QuadraticProbingTable::QuadraticProbingTable(const QuadraticProbingTable &table) : _size(
        table._size) {
    //FIXME:
}

bool QuadraticProbingTable::Insert(
        const uint8_t *key,
        const size_t &key_len,
        const uint8_t *value,
        const size_t &value_len) {
    size_t sequenceLength = 0;
    size_t hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state != BUSY) {
            _cells[index].key_len = key_len;
            _cells[index].key = key; //need copy
            _cells[index].value = value;
            _cells[index].value_len = value_len;
            _cells[index].state = BUSY;

            _size++;

            return true;
        }
        sequenceLength++;
    }
    return false;
}

bool QuadraticProbingTable::Remove(
        const uint8_t *key,
        const size_t &key_len) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

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

bool QuadraticProbingTable::Find(
        const uint8_t *key,
        const size_t &key_len) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

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

bool QuadraticProbingTable::Clear() {
    _cells.clear();

    _size = 0;

    _cells.resize(_cells.capacity());

    for (auto i = 0; i < _cells.capacity(); i++) {
        _cells[i].state = FREE;
    }

    return true;
}

size_t QuadraticProbingTable::GetSize() const {
    return _size;
}


uint8_t *QuadraticProbingTable::Get( //TODO: what return value???
        const uint8_t *key,
        const size_t &key_len) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state == BUSY && _cells[index].key == key) {
            return _cells[index].value;
        }

        if (_cells[index].state == FREE) {
            throw std::string("No value with this key");// TODO: delete throw
        }
        sequenceLength++;
    }
    throw std::string("No value with this key");// TODO: delete throw
}

QuadraticProbingTable::~QuadraticProbingTable() {
    _cells.clear();
}

bool QuadraticProbingTable::Update(
        const uint8_t *key,
        const size_t &key_len,
        const uint8_t *value,
        const size_t &value_len) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + q) % _cells.capacity();

        if (_cells[index].state == BUSY && _cells[index].key == key) {
            _cells[index].value = value;
            return true;
        }

        if (_cells[index].state == FREE) {
            throw std::string("No value with this key");// TODO: delete throw
        }
        sequenceLength++;
    }

    throw std::string("No value with this key");// TODO: delete throw
}
