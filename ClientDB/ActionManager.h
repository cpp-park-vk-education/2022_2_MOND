#ifndef MOND_DB_ACTIONMANAGER_H
#define MOND_DB_ACTIONMANAGER_H

#include "Connector.h"
#include "IActionManager.h"
#include "IConnector.h"
#include "InternalEntities.h"
#include <boost/asio/streambuf.hpp>

class ActionManager : public IActionManager {
 public:
    ActionManager() = delete;
    ActionManager(const std::string &address, const uint16_t &port) noexcept;
    ~ActionManager() override;

    bool CreateTable(const std::string &) override;
    bool DeleteTable(const std::string &) override;
    bool SelectTable(const std::string &) override;
    size_t GetNumTables() override;
    std::vector<std::string> GetTableNames() override;

    bool Insert(const std::string &key, const std::string &value) override;
    bool Remove(const std::string &key) override;
    bool Find(const std::string &key) override;
    bool Clear() override;
    size_t GetSize() override;
    std::string Get(const std::string &key) override;
    bool Update(const std::string &key, const std::string &value) override;

 private:
    void handle_request();

 private:
    Request _request;
    IConnector *_conn = nullptr;
    std::string _table_name;
};
ActionManager::ActionManager(const std::string &address, const uint16_t &port) noexcept : _conn(new Connector) {
    _conn->Connect(address, port);
}

ActionManager::~ActionManager() {
    _conn->Disconnect();
    delete _conn;
}

void ActionManager::handle_request() {
    boost::asio::streambuf buff;

    std::ostream oss(&buff);
    _request.save(oss);

    _conn->Write(buff);

    _conn->Read(buff);

    std::stringstream ss;
    ss << oss.rdbuf();
    auto ssData = ss.str();
    _request.load(ssData);
}

bool ActionManager::CreateTable(const std::string &table_name) {
    _request = Request(
            RequestType::CREATE_TABLE,
            Status::NOTHING,
            std::string(),
            std::string(),
            table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::DeleteTable(const std::string &table_name) {
    _request = Request(
            RequestType::DELETE_TABLE,
            Status::NOTHING,
            std::string(),
            std::string(),
            table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::SelectTable(const std::string &table_name) {
    _request = Request(
            RequestType::GET_TABLE,
            Status::NOTHING,
            std::string(),
            std::string(),
            table_name);

    handle_request();
    _table_name = _request._table_name;
    return _request._status == Status::OK;
}

size_t ActionManager::GetNumTables() {
    _request = Request(
            RequestType::GET_NUM_TABLES,
            Status::NOTHING,
            std::string(),
            std::string(),
            _table_name);

    handle_request();

    return 1;//TODO: serializer
}

std::vector<std::string> ActionManager::GetTableNames() {
    _request = Request(
            RequestType::SHOW_TABLES,
            Status::NOTHING,
            std::string(),
            std::string(),
            _table_name);

    handle_request();

    return std::vector<std::string>();//TODO: serializer
}

bool ActionManager::Insert(const std::string &key, const std::string &value) {
    _request = Request(
            RequestType::INSERT,
            Status::NOTHING,
            key,
            value,
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::Remove(const std::string &key) {
    _request = Request(
            RequestType::REMOVE,
            Status::NOTHING,
            key,
            std::string(),
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::Find(const std::string &key) {
    _request = Request(
            RequestType::FIND,
            Status::NOTHING,
            key,
            std::string(),
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::Clear() {
    _request = Request(
            RequestType::CLEAR,
            Status::NOTHING,
            std::string(),
            std::string(),
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

size_t ActionManager::GetSize() {
    _request = Request(
            RequestType::GET_SIZE,
            Status::NOTHING,
            std::string(),
            std::string(),
            _table_name);

    handle_request();

    return 1;//TODO: serializer
}

std::string ActionManager::Get(const std::string &key) {
    _request = Request(
            RequestType::GET,
            Status::NOTHING,
            key,
            std::string(),
            _table_name);

    handle_request();

    return _request._value;
}

bool ActionManager::Update(const std::string &key, const std::string &value) {
    _request = Request(
            RequestType::UPDATE,
            Status::NOTHING,
            key,
            value,
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

#endif// MOND_DB_ACTIONMANAGER_H
