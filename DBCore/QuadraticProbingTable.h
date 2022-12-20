// Copyright 2022 mora

#pragma once

#include "IHashTable.h"

#include <fstream>
#include <functional>
#include <utility>
#include <vector>

enum class nodeStatus { FREE,
                        BUSY,
                        REMOVED };

template<typename Key, typename Value>
class QuadraticProbingTable : public IHashTable<Key, Value> {
protected:
    const static size_t MINIMAL_SIZE = 4096;
    const static size_t MINIMAL_NODE_COUNT = 4;
    constexpr const static double REHASH_INDEX = 0.75;

    struct HashNode {
        nodeStatus _state = nodeStatus::FREE;
        Key _key;
        Value _value;

        HashNode() = default;
        HashNode(const nodeStatus &status, const Key &key, const Value &value);
        HashNode(const HashNode &other);
        HashNode(HashNode &&other) noexcept;

        HashNode &operator=(const HashNode &) = default;
        HashNode &operator=(HashNode &&) noexcept = default;

        ~HashNode() = default;
    };

    struct NodeHub {
        std::vector<HashNode> _node_hub;
        size_t _last_version = 0;
    };

    size_t _size;
    std::vector<NodeHub> _cells;
    const std::function<size_t(const Key &)> _hash;

public:
    explicit QuadraticProbingTable(
            const std::function<size_t(const Key &)> &hash);
    QuadraticProbingTable(
            const size_t &tableSize, const std::function<size_t(const Key &)> &hash);
    QuadraticProbingTable(const QuadraticProbingTable &table);
    ~QuadraticProbingTable() override;

    bool Insert(const Key &key, const Value &value) override;
    bool Remove(const Key &key) override;
    [[nodiscard]] bool Find(const Key &key) const override;
    bool Clear() override;
    [[nodiscard]] size_t GetSize() const override;
    [[nodiscard]] Value Get(const Key &key) const override;
    bool Update(const Key &key, const Value &value) override;

    [[nodiscard]] std::vector<Key> GetKeys() override;

protected:
    void grow();
};

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::HashNode::HashNode(
        const QuadraticProbingTable::HashNode &other)
    : _state(other._state), _key(other._key), _value(other._value) {}

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::HashNode::HashNode(
        QuadraticProbingTable::HashNode &&other) noexcept
    : _state(other._state),
      _key(std::move(other._key)),
      _value(std::move(other._value)) {}

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::HashNode::HashNode(
        const nodeStatus &status, const Key &key, const Value &value)
    : _state(status), _key(key), _value(value) {}

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::QuadraticProbingTable(
        const std::function<size_t(const Key &)> &hash)
    : _size(0), _hash(hash) {
    _cells.resize(MINIMAL_SIZE);

    for (auto &it: _cells) {
        it._node_hub.resize(MINIMAL_NODE_COUNT);
    }
}

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::QuadraticProbingTable(
        const size_t &tableSize, const std::function<size_t(const Key &)> &hash)
    : _size(0), _hash(hash) {
    if (tableSize < MINIMAL_SIZE) {
        _cells.resize(MINIMAL_SIZE);
    } else {
        _cells.resize(tableSize);
    }

    for (auto &it: _cells) {
        it._node_hub.resize(MINIMAL_NODE_COUNT);
    }
}

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::QuadraticProbingTable(
        const QuadraticProbingTable &table)
    : _size(table._size), _hash(table._hash) {
    _cells.resize(table._size);

    for (auto &it: _cells) {
        it._node_hub.resize(MINIMAL_NODE_COUNT);
    }

    std::copy(table._cells.begin(), table._cells.end(), _cells.begin());
}

template<typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Insert(const Key &key,
                                               const Value &value) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    if (((double) _size / (double) _cells.capacity()) >= REHASH_INDEX) {
        grow();
    }

    auto first_deleted_index = UINT64_MAX;

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();
        auto last_version = _cells[index]._last_version;

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::BUSY &&
            _cells[index]._node_hub[last_version]._key == key) {
            return false;
        }

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::REMOVED &&
            first_deleted_index == UINT64_MAX) {
            first_deleted_index = index;
        }

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::FREE) {
            _cells[index]._node_hub[last_version] = HashNode(nodeStatus::BUSY, key, value);
            _size++;
            return true;
        }
        sequenceLength++;
    }

    if (first_deleted_index != UINT64_MAX) {
        _cells[first_deleted_index]._node_hub[_cells[first_deleted_index]._last_version] = HashNode(nodeStatus::BUSY, key, value);
        _size++;
        return true;
    }

    return false;
}

template<typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Remove(const Key &key) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();
        auto last_version = _cells[index]._last_version;

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::BUSY &&
            _cells[index]._node_hub[last_version]._key == key) {
            _cells[index]._node_hub[last_version]._state = nodeStatus::REMOVED;
            _size--;
            return true;
        }

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::FREE) {
            return false;
        }
        sequenceLength++;
    }
    return false;
}

template<typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Find(const Key &key) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();
        auto last_version = _cells[index]._last_version;

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::BUSY &&
            _cells[index]._node_hub[last_version]._key == key) {
            return true;
        }

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::FREE) {
            return false;
        }
        sequenceLength++;
    }
    return false;
}

template<typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Clear() {
    for (auto &it: _cells) {
        it._node_hub.clear();
    }

    _cells.clear();
    _size = 0;
    _cells.resize(MINIMAL_SIZE);

    for (auto &it: _cells) {
        it._node_hub.resize(MINIMAL_NODE_COUNT);
    }
    return true;
}

template<typename Key, typename Value>
size_t QuadraticProbingTable<Key, Value>::GetSize() const {
    return _size;
}

template<typename Key, typename Value>
Value QuadraticProbingTable<Key, Value>::Get(const Key &key) const {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();
        auto last_version = _cells[index]._last_version;

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::BUSY &&
            _cells[index]._node_hub[last_version]._key == key) {
            return _cells[index]._node_hub[last_version]._value;
        }

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::FREE) {
            return {};
        }
        sequenceLength++;
    }
    return {};
}

template<typename Key, typename Value>
QuadraticProbingTable<Key, Value>::~QuadraticProbingTable() {
    for (auto &it: _cells) {
        it._node_hub.clear();
    }
    _cells.clear();
}

template<typename Key, typename Value>
bool QuadraticProbingTable<Key, Value>::Update(const Key &key,
                                               const Value &value) {
    size_t sequenceLength = 0;
    auto hash = _hash(key);

    for (; sequenceLength < _cells.capacity();) {
        auto q = sequenceLength * sequenceLength;
        auto index = (hash + sequenceLength / 2 + q / 2) % _cells.capacity();
        auto last_version = _cells[index]._last_version;

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::BUSY &&
            _cells[index]._node_hub[last_version]._key == key) {
            _cells[index]._last_version = (_cells[index]._last_version + 1) % MINIMAL_NODE_COUNT;

            _cells[index]._node_hub[_cells[index]._last_version]._state = nodeStatus::BUSY;
            _cells[index]._node_hub[_cells[index]._last_version]._key = key;
            _cells[index]._node_hub[_cells[index]._last_version]._value = value;

            return true;
        }

        if (_cells[index]._node_hub[last_version]._state == nodeStatus::FREE) {
            return false;
        }
        sequenceLength++;
    }

    return false;
}

template<typename Key, typename Value>
void QuadraticProbingTable<Key, Value>::grow() {
    std::vector<NodeHub> tmp;
    tmp.resize(_size);

    for (auto &it: tmp) {
        it._node_hub.resize(MINIMAL_NODE_COUNT);
    }

    std::copy_if(
            _cells.begin(), _cells.end(), tmp.begin(),
            [](const NodeHub &x) -> bool {
                return x._node_hub[x._last_version]._state == nodeStatus::BUSY;
            });

    auto cap = _cells.capacity();
    _cells.clear();
    _size = 0;
    _cells.resize(cap * 2);
    for (auto &it: _cells) {
        it._node_hub.resize(MINIMAL_NODE_COUNT);
    }

    for (auto &it_hub: tmp) {
        Insert(it_hub._node_hub[0]._key, it_hub._node_hub[0]._value);
        for (size_t i = 1; i < it_hub._node_hub.size(); ++i) {
            Update(it_hub._node_hub[i]._key, it_hub._node_hub[i]._value);
        }
    }
}
template<typename Key, typename Value>
std::vector<Key> QuadraticProbingTable<Key, Value>::GetKeys() {
    std::vector<Key> result;

    for (auto &it: _cells) {
        if (it._node_hub[it._last_version]._state == nodeStatus::BUSY) {
            result.push_back(it._node_hub[it._last_version]._key);
        }
    }

    return result;
}
