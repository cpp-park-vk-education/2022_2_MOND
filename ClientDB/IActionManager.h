#ifndef MOND_DB_IACTIONMANAGER_H
#define MOND_DB_IACTIONMANAGER_H

#include <iostream>
#include <vector>

class IActionManager {
public:
    virtual bool CreateTable(const std::string &) = 0;
    virtual bool DeleteTable(const std::string &) = 0;
    virtual bool SelectTable(const std::string &) = 0;
    virtual size_t GetNumTables() = 0;
    virtual std::vector<std::string> GetTableNames() = 0;

    virtual bool Insert(const std::string &key, const std::string &value) = 0;
    virtual bool Remove(const std::string &key) = 0;
    virtual bool Find(const std::string &key) = 0;
    virtual bool Clear() = 0;
    virtual size_t GetSize() = 0;
    virtual std::string Get(const std::string &key) = 0;
    virtual bool Update(const std::string &key, const std::string &value) = 0;

    virtual ~IActionManager() = default;
};
#endif// MOND_DB_IACTIONMANAGER_H
