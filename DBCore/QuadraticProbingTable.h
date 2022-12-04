// Copyright 2022 mora

#pragma once

#include <cstring>
#include <fstream>
#include <functional>
#include <utility>
#include <vector>

#include "IHashTable.h"

enum class nodeStatus { FREE = 0, BUSY = 1, REMOVED = 2 };

template <typename Key, typename Value>
class QuadraticProbingTable : public IHashTable<Key, Value> {
   protected:
    const static size_t MINIMAL_SIZE = 8;
    constexpr const static double REHASH_INDEX = 0.75;

    struct HashNode {
        nodeStatus state = nodeStatus::FREE;
        Key key;
        Value value;

        HashNode() = default;
        HashNode(const nodeStatus& status, const Key& key, const Value& value);
        HashNode(const HashNode& other);
        HashNode(HashNode&& other) noexcept;

        HashNode& operator=(const HashNode&) = default;
        HashNode& operator=(HashNode&&) noexcept = default;

        ~HashNode() = default;
    };

    size_t _size;
    std::vector<HashNode> _cells;
    const std::function<size_t(const Key&)> _hash;

   public:
    explicit QuadraticProbingTable(
        const std::function<size_t(const Key&)>& hash);
    QuadraticProbingTable(
        const size_t& tableSize, const std::function<size_t(const Key&)>& hash);
    QuadraticProbingTable(const QuadraticProbingTable& table);
    ~QuadraticProbingTable() override;

    bool Insert(const Key& key, const Value& value) override;
    bool Remove(const Key& key) override;
    [[nodiscard]] bool Find(const Key& key) const override;
    bool Clear() override;
    [[nodiscard]] size_t GetSize() const override;
    [[nodiscard]] Value Get(const Key& key) const override;
    bool Update(const Key& key, const Value& value) override;

    std::vector<Key> GetKeys() override;

   protected:
    void grow() override;
};

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::HashNode::HashNode(
    const QuadraticProbingTable::HashNode& other)
    : state(other.state), key(other.key), value(other.value) {}

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::HashNode::HashNode(
    QuadraticProbingTable::HashNode&& other) noexcept
    : state(other.state),
      key(std::move(other.key)),
      value(std::move(other.value)) {}

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::HashNode::HashNode(
    const nodeStatus& status, const Key& key, const Value& value)
    : state(status), key(key), value(value) {}

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::QuadraticProbingTable(
    const std::function<size_t(const Key&)>& hash)
    : _size(0), _hash(hash) {
    _cells.resize(MINIMAL_SIZE);
}

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::QuadraticProbingTable(
    const size_t& tableSize, const std::function<size_t(const Key&)>& hash)
    : _size(0), _hash(hash) {
    if (tableSize < MINIMAL_SIZE) {
        _cells.resize(MINIMAL_SIZE);
    } else {
        _cells.resize(tableSize);
    }
}

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::QuadraticProbingTable(
    const QuadraticProbingTable& table)
    : _size(table._size), _hash(table._hash) {
    _cells.resize(table._size);
    std::copy(table._cells.begin(), table._cells.end(), _cells.begin());
}

template <typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Insert(const Key& key,
                                               const Value& value) {
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
        _size++;
        return true;
    }

    return false;
}

template <typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Remove(const Key& key) {
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

template <typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Find(const Key& key) const {
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

template <typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Clear() {
    _cells.clear();
    _size = 0;
    _cells.resize(MINIMAL_SIZE);
    return true;
}

template <typename Key, typename Value>
size_t QuadraticProbingTable<Key, Value>::GetSize() const {
    return _size;
}

template <typename Key, typename Value>
Value QuadraticProbingTable<Key, Value>::Get(const Key& key) const {
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
            return {};
        }
        sequenceLength++;
    }
    return {};
}

template <typename Key, typename Value>
QuadraticProbingTable<Key, Value>::~QuadraticProbingTable() {
    _cells.clear();
}

template <typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Update(const Key& key,
                                               const Value& value) {
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

template <typename Key, typename Value>
void QuadraticProbingTable<Key, Value>::grow() {
    std::vector<HashNode> tmp;
    tmp.resize(_size);
    std::copy_if(
        _cells.begin(), _cells.end(), tmp.begin(),
        [](const HashNode& x) -> bool { return x.state == nodeStatus::BUSY;
        });

    auto cap = _cells.capacity();
    _cells.clear();
    _size = 0;
    _cells.resize(cap * 2);

    for (HashNode& it : tmp) {
        Insert(it.key, it.value);
    }
}
template <typename Key, typename Value>
std::vector<Key> QuadraticProbingTable<Key, Value>::GetKeys() {
    std::vector<Key> result;

    for (auto &it : _cells) {
        if(it.state == nodeStatus::BUSY){
            result.push_back(it.key);
        }
    }

    return result;
}
