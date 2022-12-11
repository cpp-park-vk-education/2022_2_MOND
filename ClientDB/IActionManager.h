#ifndef MOND_DB_IACTIONMANAGER_H
#define MOND_DB_IACTIONMANAGER_H

#include <iostream>
#include <vector>

class IActionManager {
    virtual bool CreateTable(const std::string &) = 0;
    virtual bool DeleteTable(const std::string &) = 0;
    virtual bool SelectTable(const std::string &) = 0;
    virtual size_t GetNumTables() = 0;
    virtual std::vector<std::string> GetTableNames() = 0;

    virtual bool Insert(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) = 0;
    virtual bool Remove(const std::vector<uint8_t> &key) = 0;
    virtual bool Find(const std::vector<uint8_t> &key) = 0;
    virtual bool Clear() = 0;
    virtual size_t GetSize() = 0;
    virtual std::vector<uint8_t> Get(const std::vector<uint8_t> &key) = 0;
    virtual bool Update(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) = 0;
};
#endif// MOND_DB_IACTIONMANAGER_H
