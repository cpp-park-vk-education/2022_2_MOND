#ifndef HASHMAPBD_HASHTABLE_H
#define HASHMAPBD_HASHTABLE_H

#pragma once

#include <iostream>

/* Интерфейс хеш-таблицы */

template<typename K, typename T>
class HashTableInterface {
public:
    virtual bool Insert(const K &key, const T &value) = 0; // добавление значения по ключу

    virtual bool Remove(const K &key) = 0; // удаление по ключу

    virtual bool Find(const K &key) const = 0; // поиск по ключу

    virtual bool Clear() = 0; // очистка таблицы

    virtual uint32_t GetSize() const = 0; // получение числа элементов

    virtual bool IsEmpty() const = 0; // проверка на пустоту

    virtual T Get(const K &key) const = 0; // получение значения по ключу

    virtual void ChangeValue(const K &key, const T &value) = 0; // поменять значение в ноде

    virtual bool PrintToFile(const std::string &path, uint32_t sizeOfNode) const = 0; // напечатать базу в файл

    virtual uint8_t *ReadFromFile(const std::string &path, uint32_t *outsize) const = 0; // прочитать базу их файла

    virtual ~HashTableInterface() {}
};

#endif //HASHMAPBD_HASHTABLE_H
