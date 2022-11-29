// Copyright 2022 mora

#pragma once

#include "IHashTable.h"

#include <cstring>
#include <fstream>
#include <utility>
#include <vector>
#include <functional>

enum class nodeStatus {
    FREE = 0,
    BUSY = 1,
    REMOVED = 2
};

class QuadraticProbingTable : public IHashTable {
private:
    const static size_t MINIMAL_SIZE = 8;
    constexpr const static double REHASH_INDEX = 0.75;

    struct HashNode {
        size_t key_len = 0;
        size_t value_len = 0;
        nodeStatus state = nodeStatus::FREE;
        uint8_t *key = nullptr;
        uint8_t *value = nullptr;

        HashNode() = default;
        HashNode(
                const size_t &key_len,
                const size_t &value_len,
                const nodeStatus &status,
                uint8_t *key,
                uint8_t *value);
        HashNode(const HashNode &other);
        HashNode(HashNode &&other) noexcept;
        HashNode &operator=(const HashNode &);
        HashNode &operator=(HashNode &&) noexcept;

        ~HashNode();
    };

    size_t _size;
    std::vector<HashNode> _cells;
    const std::function<size_t(const uint8_t *, const size_t &)> _hash;

public:
    explicit QuadraticProbingTable(std::function<size_t(const uint8_t *, const size_t &)> hash);
    QuadraticProbingTable(const uint32_t &tableSize, std::function<size_t(const uint8_t *, const size_t &)> hash);
    QuadraticProbingTable(const QuadraticProbingTable &table);
    ~QuadraticProbingTable() override;

    bool Insert(uint8_t *key,
                const size_t &key_len,
                uint8_t *value,
                const size_t &value_len) override;
    bool Remove(const uint8_t *key,
                const size_t &key_len) override;
    bool Find(const uint8_t *key,
              const size_t &key_len) const override;
    bool Clear() override;
    [[nodiscard]] size_t GetSize() const override;
    uint8_t *Get(const uint8_t *key,
                 const size_t &key_len) const override;
    bool Update(uint8_t *key,
                const size_t &key_len,
                uint8_t *value,
                const size_t &value_len) override;

private:
    void grow() override;
};

QuadraticProbingTable::HashNode::HashNode(const QuadraticProbingTable::HashNode &other)
        : key_len(other.key_len),
          value_len(other.value_len),
          state(other.state) {
    key = new uint8_t[key_len];
    value = new uint8_t[value_len];

    memcpy(key, other.key, key_len);
    memcpy(value, other.value, value_len);
}

QuadraticProbingTable::HashNode::HashNode(QuadraticProbingTable::HashNode &&other) noexcept
        : key_len(other.key_len),
          value_len(other.value_len),
          state(other.state){
    key = other.key;
    value = other.value;

    other.key = nullptr;
    other.value = nullptr;
}

QuadraticProbingTable::HashNode &QuadraticProbingTable::HashNode
::operator=(const QuadraticProbingTable::HashNode &other) {
    if (&other != this) {
        delete[] key;
        delete[] value;

        key_len = other.key_len;
        value_len = other.value_len;
        state = other.state;

        key = new uint8_t[key_len];
        value = new uint8_t[value_len];

        memcpy(key, other.key, key_len);
        memcpy(value, other.value, value_len);
    }
    return *this;
}

QuadraticProbingTable::HashNode &
QuadraticProbingTable::HashNode::operator=(QuadraticProbingTable::HashNode &&other) noexcept {
    delete key;
    delete value;

    key_len = other.key_len;
    value_len = other.value_len;
    state = other.state;

    key = new uint8_t[key_len];
    value = new uint8_t[value_len];

    memcpy(key, other.key, key_len);
    memcpy(value, other.value, value_len);

    other.key = nullptr;
    other.value = nullptr;

    return *this;
}

QuadraticProbingTable::HashNode::~HashNode() {
    if (key) {
        std::cout << unsigned(key[0]) << unsigned(key[1]) << " | ";
    }
    delete[] key;
    delete[] value;
}

QuadraticProbingTable::HashNode::HashNode(
        const size_t &key_len,
        const size_t &value_len,
        const nodeStatus &status,
        uint8_t *key,
        uint8_t *value)
        : key_len(key_len),
          value_len(value_len),
          state(status),
          key(key),
          value(value) {
}

QuadraticProbingTable::QuadraticProbingTable(std::function<size_t(const uint8_t *, const size_t &)> hash)
: _size(0), _hash(std::move(hash)) {
    _cells.resize(MINIMAL_SIZE);
}

QuadraticProbingTable::QuadraticProbingTable(
        const uint32_t &tableSize,
        std::function<size_t(const uint8_t *, const size_t &)> hash)
        : _size(0), _hash(std::move(hash)) {
    if (tableSize < MINIMAL_SIZE){
        _cells.resize(MINIMAL_SIZE);
    }else{
        _cells.resize(tableSize);
    }
}

QuadraticProbingTable::QuadraticProbingTable(const QuadraticProbingTable &table)
: _size(table._size), _hash(table._hash) {
    _cells.resize(table._size);
    std::copy(table._cells.begin(), table._cells.end(), _cells.begin());
}

bool QuadraticProbingTable::Insert(
        uint8_t *key,
        const size_t &key_len,
        uint8_t *value,
        const size_t &value_len) {

    size_t sequenceLength = 0;
    auto hash = _hash(key, key_len);

    if (((double) _size / (double) _cells.capacity()) >= REHASH_INDEX) {
        grow();
    }

    auto first_deleted_index = UINT64_MAX;

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY
            && _cells[index].key_len == key_len
            && !memcmp(_cells[index].key, key, key_len)) {
            return false;
        }

        if (_cells[index].state == nodeStatus::REMOVED
            && first_deleted_index == UINT64_MAX) {
            first_deleted_index = index;
        }

        if (_cells[index].state == nodeStatus::FREE) {
            _cells[index] = HashNode(key_len, value_len, nodeStatus::BUSY, key, value);
            _size++;
            return true;
        }
        sequenceLength++;
    }

    if (first_deleted_index != UINT64_MAX) {
        _cells[first_deleted_index] = HashNode(key_len, value_len, nodeStatus::BUSY, key, value);;
        _size++;
        return true;
    }

    return false;
}

bool QuadraticProbingTable::Remove(
        const uint8_t *key,
        const size_t &key_len) {
    size_t sequenceLength = 0;
    auto hash = _hash(key, key_len);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY
            && _cells[index].key_len == key_len
            && !memcmp(_cells[index].key, key, key_len)) {
            _cells[index].state = nodeStatus::REMOVED;
            _size--;
            return true;
        }

        if (_cells[index].state == nodeStatus::FREE) {
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
    auto hash = _hash(key, key_len);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY
            && _cells[index].key_len == key_len
            && !memcmp(_cells[index].key, key, key_len)) {
            return true;
        }

        if (_cells[index].state == nodeStatus::FREE) {
            return false;
        }
        sequenceLength++;
    }
    return false;
}

bool QuadraticProbingTable::Clear() {
    HashNode* a = &_cells[0];
    _cells.clear();
    _size = 0;
    _cells.resize(MINIMAL_SIZE);
    return true;
}

size_t QuadraticProbingTable::GetSize() const {
    return _size;
}

uint8_t *QuadraticProbingTable::Get(
        const uint8_t *key,
        const size_t &key_len) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key, key_len);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY
            && _cells[index].key_len == key_len
            && !memcmp(_cells[index].key, key, key_len)) {
            return _cells[index].value;
        }

        if (_cells[index].state == nodeStatus::FREE) {
            return nullptr;
        }
        sequenceLength++;
    }
    return nullptr;
}

QuadraticProbingTable::~QuadraticProbingTable() {
    _cells.clear();
}

bool QuadraticProbingTable::Update(
        uint8_t *key,
        const size_t &key_len,
        uint8_t *value,
        const size_t &value_len) {
    size_t sequenceLength = 0;
    auto hash = _hash(key, key_len);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY
            && _cells[index].key_len == key_len
            && !memcmp(_cells[index].key, key, key_len)) {
            if(_cells[index].value_len == value_len){
                memcpy(_cells[index].value, value, value_len);
                return true;
            }else{
                return false;
            }
        }

        if (_cells[index].state == nodeStatus::FREE) {
            return false;
        }
        sequenceLength++;
    }

    return false;
}

void QuadraticProbingTable::grow() {
    std::vector<HashNode> tmp;
    tmp.resize(_size);
    std::copy_if(_cells.begin(), _cells.end(), tmp.begin(), [](const HashNode& x) -> bool {
        return x.state == nodeStatus::BUSY;
    });

    auto cap = _cells.capacity();
    _cells.clear();
    _size = 0;
    _cells.resize(cap * 2);

    for (HashNode &it : tmp) {
        Insert(it.key, it.key_len, it.value, it.value_len);
    }
}
