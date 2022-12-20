//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_CONNECTIONHANDLER_H
#define MOND_DB_CONNECTIONHANDLER_H

#include "AccessController.h"
#include "IAccessController.h"
#include "IConnectionHandler.h"
#include "ITableStorage.h"

#include <boost/bind.hpp>
#include <queue>

class ConnectionHandler : public IConnectionHandler {
 public:
    explicit ConnectionHandler(ITableStorage *storage);

    ConnectionHandler(const ConnectionHandler& other) = delete;
    ConnectionHandler(ConnectionHandler &&other) = delete;

    ConnectionHandler& operator=(ConnectionHandler &&other) = delete;
    ConnectionHandler& operator=(const ConnectionHandler &other) = delete;

    void listenConnections(boost::asio::io_context *ioContext, std::atomic_bool *stop) override;
    void handleSessions(std::atomic_bool *stop) override;

    ~ConnectionHandler() override;

 private:
    void onReadComplete(std::shared_ptr<Connection> connection, const std::error_code &err, size_t read_bytes);
    void onWriteComplete(std::shared_ptr<Connection> connection, const std::error_code &err, size_t write_bytes);

    void sendAnswer(std::shared_ptr<Connection> connection, Request request);

    void loadNewConnections();
    void setWaitingConnectionsToRecieve();
    void removeDeadConnections();

    void closeAllConnections();

    std::mutex _newConnectionsMutex;
    std::vector<std::shared_ptr<Connection>> _handledConnections;
    std::queue<std::shared_ptr<Connection>> _newConnections;
    ITableStorage *_storage;
    workerFactory _wFactory;

    IAccessController *accessController;
};

ConnectionHandler::ConnectionHandler(ITableStorage *storage) : _storage(storage) {
    accessController = new AccessController;
}

void ConnectionHandler::listenConnections(boost::asio::io_context *ioContext, std::atomic_bool *stop) {
    boost::asio::ip::tcp::acceptor acceptor(*ioContext,
                                            boost::asio::ip::tcp::endpoint(
                                                    boost::asio::ip::tcp::v4(), 6666)
    );

    acceptor.non_blocking(true);
    std::cout << "starting listen connections..." << std::endl;
    while (!(*stop)) {
        boost::system::error_code error;
        std::shared_ptr<Connection> conn = std::make_shared<Connection>(ioContext);
        acceptor.accept(conn->sock, error);

        if(error == boost::asio::error::would_block){
            continue;
        }
        _newConnectionsMutex.lock();
        _newConnections.push(std::move(conn));
        _newConnectionsMutex.unlock();
    }
}

void ConnectionHandler::handleSessions(std::atomic_bool *stop) {
    while (!(*stop)) {
        loadNewConnections();
        setWaitingConnectionsToRecieve();
        removeDeadConnections();
    }
    closeAllConnections();
}

void ConnectionHandler::onReadComplete(std::shared_ptr<Connection> connection, const std::error_code &err,
                                       size_t read_bytes) {
    if (err) {
        connection->status = ConnectionStatus::disconnected;
        return;
    }

    std::shared_ptr<Request> request = std::make_shared<Request>();

    std::ostream oss(&connection->buff);
    std::stringstream ss;
    ss << oss.rdbuf();
    std::string str_data = ss.str();
    request->load(str_data);

    IWorker *worker = _wFactory.get(request, _storage);

    accessController->getPermission(request);
    Request answer = worker->operate();
    accessController->releaseResource(request);
    delete worker;

    connection->status = ConnectionStatus::onWrite;
    sendAnswer(connection, std::move(answer));
}

void ConnectionHandler::onWriteComplete(std::shared_ptr<Connection> connection, const std::error_code &err,
                                        size_t write_bytes) {
    if (err) {
        connection->status = ConnectionStatus::disconnected;
        return;
    }
    connection->status = ConnectionStatus::waiting;
}

void ConnectionHandler::sendAnswer(std::shared_ptr<Connection> connection, Request request) {
    std::ostream oss(&connection->buff);
    request.save(oss);

    async_write(connection->sock, connection->buff,
                boost::bind(&ConnectionHandler::onWriteComplete, this, connection, _1, _2));
}

void ConnectionHandler::loadNewConnections() {
    _newConnectionsMutex.lock();
    while (!_newConnections.empty()) {
        _handledConnections.push_back(std::move(_newConnections.front()));
        _newConnections.pop();
    }
    _newConnectionsMutex.unlock();
}

void ConnectionHandler::setWaitingConnectionsToRecieve() {
    for (auto &connection: _handledConnections) {
        if (connection->status == ConnectionStatus::waiting) {
            connection->status = ConnectionStatus::onRead;
            async_read_until(connection->sock, connection->buff, delimiter,
                             boost::bind(&ConnectionHandler::onReadComplete, this, connection, _1, _2));
        }
    }
}

void ConnectionHandler::removeDeadConnections() {
    for (auto connection = _handledConnections.begin(); connection != _handledConnections.end();) {
        if ((*connection)->status == ConnectionStatus::disconnected) {
            connection = _handledConnections.erase(connection);
        } else {
            ++connection;
        }
    }
}

void ConnectionHandler::closeAllConnections() {
    for (auto connection = _handledConnections.begin(); connection != _handledConnections.end();) {
        if (((*connection)->status == ConnectionStatus::waiting)
            || ((*connection)->status == ConnectionStatus::disconnected)) {
            (*connection)->sock.close();
            connection = _handledConnections.erase(connection);
        } else {
            ++connection;
        }
    }
}

ConnectionHandler::~ConnectionHandler() {
    delete accessController;
}

#endif //MOND_DB_CONNECTIONHANDLER_H
