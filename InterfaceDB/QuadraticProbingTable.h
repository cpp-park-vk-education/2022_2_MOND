#ifndef HASHMAPBD_QUADRATICPROBINGTABLE_H
#define HASHMAPBD_QUADRATICPROBINGTABLE_H

#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "HashTable.h"

template<typename K, typename T>
class QuadraticProbingTable : public HashTableInterface<K, T> {
    const uint32_t FREE = 0; // свободная ячейка
    const uint32_t BUSY = 1; // занятая ячейка
    const uint32_t REMOVED = 2; // удалённая ячейка

    struct HashNode {
        K key; // значение ключа элемента
        T value; // значение элемента
        uint32_t state; // состояние ячейки
    };

    uint32_t capacity; // ёмкость таблицы
    uint32_t size; // число элементов в таблице
    HashNode *cells; // массив ячеек

    uint32_t (*h)(K); // указатель на хеш-функцию

public:
    QuadraticProbingTable(uint32_t tableSize, uint32_t (*h)(K)); // конструктор из размера и хеш-функции
    QuadraticProbingTable(const QuadraticProbingTable &table); // конструктор копирования

    bool Insert(const K &key, const T &value); // добавление значения по ключу
    bool Remove(const K &key); // удаление по ключу
    bool Find(const K &key) const; // поиск по ключу

    bool Clear(); // очистка таблицы

    [[nodiscard]] uint32_t GetSize() const; // получение размера
    [[nodiscard]] bool IsEmpty() const; // проверка на пустоту

    T Get(const K &key) const; // получение значения по ключу

    void ChangeValue(const K &key, const T &value);

    [[nodiscard]] bool PrintToFile(const std::string &path, uint32_t sizeOfNode) const;

    uint8_t *ReadFromFile(const std::string &path, uint32_t *outsize) const;

    ~QuadraticProbingTable();
};

// конструктор из размера и хеш-функции
template<typename K, typename T>
QuadraticProbingTable<K, T>::QuadraticProbingTable(uint32_t tableSize, uint32_t (*h)(K)) {
    this->capacity = tableSize; // запоминаем в ёмкости переданный размер
    this->size = 0; // изначально нет элементов
    this->cells = new HashNode[tableSize]; // выделяем память под ячейки

    // делаем все ячейки свободными
    for (size_t i = 0; i < tableSize; i++)
        cells[i].state = FREE;

    this->h = h; // запоминаем указатель на функцию
}

// конструктор копирования
template<typename K, typename T>
QuadraticProbingTable<K, T>::QuadraticProbingTable(const QuadraticProbingTable &table) {
    capacity = table.capacity; // копируем ёмкость
    size = table.size; // копируем количество элементов
    cells = new HashNode[capacity]; // выделяем память под массив

    h = table.h; // копируем указатель на функцию

    // проходимся по всем ячейкам таблицы и копируем их содержимое
    for (size_t i = 0; i < capacity; i++) {
        cells[i].value = table.cells[i].value;
        cells[i].key = table.cells[i].key;
        cells[i].state = table.cells[i].state;
    }
}

// добавление значения по ключу
template<typename K, typename T>
bool QuadraticProbingTable<K, T>::Insert(const K &key, const T &value) {
    uint32_t sequenceLength = 0; // начальная длина пробной последовательности равна нулю
    uint32_t hash = h(key); // получаем хеш от ключа

    for (; sequenceLength < capacity;) {
        uint32_t q = sequenceLength * sequenceLength;
        uint32_t index = (hash + q) % capacity;

        if (cells[index].state != BUSY) { // если нашли незанятую ячейку
            cells[index].key = key; // сохраняем ключ
            cells[index].value = value; // сохраняем значение
            cells[index].state = BUSY; // ячейка становится занятой

            size++; // увеличиваем счётчик числа элементов
            return true; // выходим
        }
        sequenceLength++; // увеличиваем длину пробной последовательности
    }
    // прошли всю таблицу
    return false;
}

// удаление по ключу
template<typename K, typename T>
bool QuadraticProbingTable<K, T>::Remove(const K &key) {
    uint32_t sequenceLength = 0; // начальная длина пробной последовательности равна нулю
    uint32_t hash = h(key); // получаем хеш от ключа

    for (; sequenceLength < capacity;) {
        uint32_t q = sequenceLength * sequenceLength;
        uint32_t index = (hash + q) % capacity;
        // если нашли занятую нужным ключом ячейку
        if (cells[index].state == BUSY && cells[index].key == key) {
            cells[index].state = REMOVED; // помечаем её как удалённую
            size--; // уменьшаем счётчик числа элементов
            return true; // возвращаем истину
        }
        // если нашли свободную ячейку
        if (cells[index].state == FREE)
            return false; // возвращаем ложь

        sequenceLength++; // увеличиваем длину пробной последовательности
    }
    return false; // не нашли во всей таблице, возвращаем ложь
}

// поиск по ключу
template<typename K, typename T>
bool QuadraticProbingTable<K, T>::Find(const K &key) const {
    uint32_t sequenceLength = 0; // начальная длина пробной последовательности равна нулю
    uint32_t hash = h(key); // получаем хеш от ключа

    for (; sequenceLength < capacity;) {
        uint32_t q = sequenceLength * sequenceLength;
        uint32_t index = (hash + q) % capacity; // ищем индекс элемента

        // если нашли занятую клетку с нужным ключом
        if (cells[index].state == BUSY && cells[index].key == key)
            return true; // значит нашли

        // если нашли свободную ячейку
        if (cells[index].state == FREE)
            return false; // значит нет элемента

        sequenceLength++; // увеличиваем длину пробной последовательности
    }

    return false; // не нашли во всей таблице
}

template<typename K, typename T>
bool QuadraticProbingTable<K, T>::Clear() {
    for (size_t i = 0; i < capacity; i++)
        cells[i].state = FREE;

    size = 0; // обнуляем счётчик числа элементов
    return true;
}

template<typename K, typename T>
uint32_t QuadraticProbingTable<K, T>::GetSize() const {
    return size; // возвращаем размер
}

template<typename K, typename T>
bool QuadraticProbingTable<K, T>::IsEmpty() const {
    return size == 0; // таблица пуста, если нет элементов
}

// получение значения по ключу
template<typename K, typename T>
T QuadraticProbingTable<K, T>::Get(const K &key) const {
    uint32_t sequenceLength = 0;
    uint32_t hash = h(key); // получаем хеш от ключа

    for (; sequenceLength < capacity;) {
        uint32_t q = sequenceLength * sequenceLength;
        uint32_t index = (hash + q) % capacity;

        // если нашли занятую клетку с нужным ключом
        if (cells[index].state == BUSY && cells[index].key == key)
            return cells[index].value; // значит нашли

        // если нашли свободную ячейку, значит нет такого элемента
        if (cells[index].state == FREE)
            throw std::runtime_error("No value with this key"); // бросаем исключение FIXME:

        sequenceLength++; // увеличиваем длину пробной последовательности
    }

    // обошли всю таблицу
    throw std::runtime_error("No value with this key"); // бросаем исключение FIXME:
}

// деструктор (освобождения памяти)
template<typename K, typename T>
QuadraticProbingTable<K, T>::~QuadraticProbingTable() {
    delete[] cells; // удаляем массив ячеек
}

template<typename K, typename T>
void QuadraticProbingTable<K, T>::ChangeValue(const K &key, const T &value) {
    uint32_t sequenceLength = 0;
    uint32_t hash = h(key); // получаем хеш от ключа

    for (; sequenceLength < capacity;) {
        uint32_t q = sequenceLength * sequenceLength;
        uint32_t index = (hash + q) % capacity;

        // если нашли занятую клетку с нужным ключом
        if (cells[index].state == BUSY && cells[index].key == key) {
            cells[index].value = value; // значит нашли
            return;
        }


        // если нашли свободную ячейку, значит нет такого элемента
        if (cells[index].state == FREE)
            throw std::runtime_error("No value with this key"); // бросаем исключение FIXME

        sequenceLength++; // увеличиваем длину пробной последовательности
    }

    // обошли всю таблицу
    throw std::runtime_error("No value with this key"); // бросаем исключение FIXME
}

template<typename K, typename T>
bool QuadraticProbingTable<K, T>::PrintToFile(const std::string &path, uint32_t sizeOfNode) const {
    std::ofstream outfile;
    outfile.open(path, std::ios::out | std::ios::binary);
    if (!outfile) return false;

    for (size_t i = 0; i < capacity; i++) {
        if (cells[i].state != BUSY)
            continue; // если ячейка не занята, то переходим к следующему элементу
        outfile.write((char *) (&cells[i].value), sizeOfNode);
    }
    outfile.close();
    return true;
}

template<typename K, typename T>
uint8_t *QuadraticProbingTable<K, T>::ReadFromFile(const std::string &path, uint32_t *outsize) const {
    std::streampos fileSize;
    std::ifstream infile;
    uint8_t *memblock = nullptr;

    infile.open(path, std::ios::in | std::ios::binary | std::ios::ate);

    if (!infile) return memblock;

    fileSize = infile.tellg();
    memblock = new uint8_t[fileSize];
    infile.seekg(0, std::ios::beg);
    infile.read(reinterpret_cast<char *>(memblock), fileSize);

    infile.close();

    *outsize = fileSize;

    return memblock;
}

#endif //HASHMAPBD_QUADRATICPROBINGTABLE_H
