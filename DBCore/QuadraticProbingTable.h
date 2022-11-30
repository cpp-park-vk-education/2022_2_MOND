// Copyright 2022 mora

#pragma once

#include <cstring>
#include <fstream>
#include <functional>
#include <utility>
#include <vector>

#include "IHashTable.h"

enum class nodeStatus { FREE = 0, BUSY = 1, REMOVED = 2 };

class QuadraticProbingTable : public IHashTable {
   private:
    const static size_t MINIMAL_SIZE = 8;
    constexpr const static double REHASH_INDEX = 0.75;

    struct HashNode {
        nodeStatus state = nodeStatus::FREE;
        std::vector<uint8_t> key;
        std::vector<uint8_t> value;

        HashNode() = default;
        HashNode(const nodeStatus& status, const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& value);
        HashNode(const HashNode& other);
        HashNode(HashNode&& other) noexcept;
        HashNode& operator=(const HashNode&);
        HashNode& operator=(HashNode&&) noexcept;

        ~HashNode();
    };

    size_t _size;
    std::vector<HashNode> _cells;
    const std::function<size_t(const std::vector<uint8_t>&)> _hash;

   public:
    explicit QuadraticProbingTable(
        const std::function<size_t(const std::vector<uint8_t>&)>& hash);
    QuadraticProbingTable(
        const size_t& tableSize,
        const std::function<size_t(const std::vector<uint8_t>&)>& hash);
    QuadraticProbingTable(const QuadraticProbingTable& table);
    ~QuadraticProbingTable() override;

    bool Insert(const std::vector<uint8_t>& key,
                const std::vector<uint8_t>& value) override;
    bool Remove(const std::vector<uint8_t>& key) override;
    bool Find(const std::vector<uint8_t>& key) const override;
    bool Clear() override;
    [[nodiscard]] size_t GetSize() const override;
    [[nodiscard]] std::vector<uint8_t> Get(
        const std::vector<uint8_t>& key) const override;
    bool Update(const std::vector<uint8_t>& key,
                const std::vector<uint8_t>& value) override;

   private:
    void grow() override;
};

QuadraticProbingTable::HashNode::HashNode(
    const QuadraticProbingTable::HashNode& other)
    : state(other.state), key(other.key), value(other.value) {}

QuadraticProbingTable::HashNode::HashNode(
    QuadraticProbingTable::HashNode&& other) noexcept
    : state(other.state),
      key(std::move(other.key)),
      value(std::move(other.value)) {}

QuadraticProbingTable::HashNode& QuadraticProbingTable::HashNode ::operator=(
    const QuadraticProbingTable::HashNode& other) {
    if (&other != this) {
        key.clear();
        value.clear();

        state = other.state;

        key = other.key;
        value = other.value;
    }
    return *this;
}

QuadraticProbingTable::HashNode& QuadraticProbingTable::HashNode::operator=(
    QuadraticProbingTable::HashNode&& other) noexcept {
    key.clear();
    value.clear();

    state = other.state;

    key = std::move(other.key);
    value = std::move(other.value);

    return *this;
}

QuadraticProbingTable::HashNode::~HashNode() {
    key.clear();
    value.clear();
}

QuadraticProbingTable::HashNode::HashNode(const nodeStatus& status,
                                          const std::vector<uint8_t>& key,
                                          const std::vector<uint8_t>& value)
    : state(status), key(key), value(value) {}

QuadraticProbingTable::QuadraticProbingTable(
    const std::function<size_t(const std::vector<uint8_t>&)>& hash)
    : _size(0), _hash(std::move(hash)) {
    _cells.resize(MINIMAL_SIZE);
}

QuadraticProbingTable::QuadraticProbingTable(
    const size_t& tableSize,
    const std::function<size_t(const std::vector<uint8_t>&)>& hash)
    : _size(0), _hash(std::move(hash)) {
    if (tableSize < MINIMAL_SIZE) {
        _cells.resize(MINIMAL_SIZE);
    } else {
        _cells.resize(tableSize);
    }
}

QuadraticProbingTable::QuadraticProbingTable(const QuadraticProbingTable& table)
    : _size(table._size), _hash(table._hash) {
    _cells.resize(table._size);
    std::copy(table._cells.begin(), table._cells.end(), _cells.begin());
}

bool QuadraticProbingTable::Insert(const std::vector<uint8_t>& key,
                                   const std::vector<uint8_t>& value) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    if (((double)_size / (double)_cells.capacity()) >= REHASH_INDEX) {
        grow();
    }

    auto first_deleted_index = UINT64_MAX;

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY &&
            _cells[index].key == key) {
            return false;
        }

        if (_cells[index].state == nodeStatus::REMOVED &&
            first_deleted_index == UINT64_MAX) {
            first_deleted_index = index;
        }

        if (_cells[index].state == nodeStatus::FREE) {
            _cells[index] = HashNode(nodeStatus::BUSY, key, value);
            _size++;
            return true;
        }
        sequenceLength++;
    }

    if (first_deleted_index != UINT64_MAX) {
        _cells[first_deleted_index] = HashNode(nodeStatus::BUSY, key, value);
        ;
        _size++;
        return true;
    }

    return false;
}

bool QuadraticProbingTable::Remove(const std::vector<uint8_t>& key) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY &&
            _cells[index].key == key) {
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

bool QuadraticProbingTable::Find(const std::vector<uint8_t>& key) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY &&
            _cells[index].key == key) {
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
    _cells.clear();
    _size = 0;
    _cells.resize(MINIMAL_SIZE);
    return true;
}

size_t QuadraticProbingTable::GetSize() const { return _size; }

std::vector<uint8_t> QuadraticProbingTable::Get(
    const std::vector<uint8_t>& key) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY &&
            _cells[index].key == key) {
            return _cells[index].value;
        }

        if (_cells[index].state == nodeStatus::FREE) {
            return std::vector<uint8_t>();
        }
        sequenceLength++;
    }
    return std::vector<uint8_t>();
}

QuadraticProbingTable::~QuadraticProbingTable() { _cells.clear(); }

bool QuadraticProbingTable::Update(const std::vector<uint8_t>& key,
                                   const std::vector<uint8_t>& value) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();

        if (_cells[index].state == nodeStatus::BUSY &&
            _cells[index].key == key) {
            _cells[index].value = value;
            return true;
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
    std::copy_if(
        _cells.begin(), _cells.end(), tmp.begin(),
        [](const HashNode& x) -> bool { return x.state == nodeStatus::BUSY; });

    auto cap = _cells.capacity();
    _cells.clear();
    _size = 0;
    _cells.resize(cap * 2);

    for (HashNode& it : tmp) {
        Insert(it.key, it.value);
    }
}
