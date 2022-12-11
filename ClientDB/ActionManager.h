#ifndef MOND_DB_ACTIONMANAGER_H
#define MOND_DB_ACTIONMANAGER_H

#include "IActionManager.h"
#include "InternalEntities.h"

class ActionManager : public IActionManager {
public:
    bool CreateTable(const std::string &) override;
    bool DeleteTable(const std::string &) const override;
    bool SelectTable(const std::string &) const override;
    size_t GetNumTables() const override;
    std::vector<std::string> GetTableNames() const override;

    bool Insert(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) const override;
    bool Remove(const std::vector<uint8_t> &key) const override;
    bool Find(const std::vector<uint8_t> &key) const override;
    bool Clear() const override;
    size_t GetSize() const override;
    std::vector<uint8_t> Get(const std::vector<uint8_t> &key) const override;
    bool Update(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) const override;

private:
    Request request;
};
bool ActionManager::CreateTable(const std::string &table_name) {

    return false;
}
#endif// MOND_DB_ACTIONMANAGER_H
