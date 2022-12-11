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
    ~ActionManager();

    bool CreateTable(const std::string &) override;
    bool DeleteTable(const std::string &) override;
    bool SelectTable(const std::string &) override;
    size_t GetNumTables() override;
    std::vector<std::string> GetTableNames() override;

    bool Insert(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) override;
    bool Remove(const std::vector<uint8_t> &key) override;
    bool Find(const std::vector<uint8_t> &key) override;
    bool Clear() override;
    size_t GetSize() override;
    std::vector<uint8_t> Get(const std::vector<uint8_t> &key) override;
    bool Update(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) override;

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

    _request.load(ss.str());
}

bool ActionManager::CreateTable(const std::string &table_name) {
    _request = Request(
            requestType::CREATE_TABLE,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::DeleteTable(const std::string &table_name) {
    _request = Request(
            requestType::DELETE_TABLE,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::SelectTable(const std::string &table_name) {
    _request = Request(
            requestType::GET_TABLE,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            table_name);

    handle_request();

    return _request._status == Status::OK;
}

size_t ActionManager::GetNumTables() {
    _request = Request(
            requestType::GET_NUM_TABLES,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return 1;//TODO: serializer
}

std::vector<std::string> ActionManager::GetTableNames() {
    _request = Request(
            requestType::SHOW_TABLES,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return std::vector<std::string>();//TODO: serializer
}

bool ActionManager::Insert(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) {
    _request = Request(
            requestType::INSERT,
            Status::NOTHING,
            key,
            value,
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::Remove(const std::vector<uint8_t> &key) {
    _request = Request(
            requestType::REMOVE,
            Status::NOTHING,
            key,
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::Find(const std::vector<uint8_t> &key) {
    _request = Request(
            requestType::FIND,
            Status::NOTHING,
            key,
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

bool ActionManager::Clear() {
    _request = Request(
            requestType::CLEAR,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

size_t ActionManager::GetSize() {
    _request = Request(
            requestType::GET_SIZE,
            Status::NOTHING,
            std::vector<uint8_t>(),
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return 1;//TODO: serializer
}

std::vector<uint8_t> ActionManager::Get(const std::vector<uint8_t> &key) {
    _request = Request(
            requestType::GET,
            Status::NOTHING,
            key,
            std::vector<uint8_t>(),
            _table_name);

    handle_request();

    return _request._value;
}

bool ActionManager::Update(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value) {
    _request = Request(
            requestType::UPDATE,
            Status::NOTHING,
            key,
            value,
            _table_name);

    handle_request();

    return _request._status == Status::OK;
}

#endif// MOND_DB_ACTIONMANAGER_H
