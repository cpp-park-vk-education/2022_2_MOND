//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_CONNECTIONHANDLER_H
#define MOND_DB_CONNECTIONHANDLER_H

#include <queue>
#include "IConnectionHandler.h"
#include <boost/bind.hpp>


class ConnectionHandler : public IConnectionHandler {
public:
    explicit ConnectionHandler(ITableStorage* storage): _storage(storage){}

    ITableStorage* getStorage() override {
        return _storage;
    }

    void listenConnections(boost::asio::io_context *ioContext, std::atomic_bool* stop) override {
        boost::asio::ip::tcp::acceptor acceptor(*ioContext,
                                                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001));
        std::cout << "starting listen connections..." << std::endl;
        while (!(*stop)) {
            std::shared_ptr<Connection> conn = std::make_shared<Connection>(ioContext);
            acceptor.accept(conn->sock);
            _newConnectionsMutex.lock();
            _newConnections.push(std::move(conn));
            _newConnectionsMutex.unlock();
        }
    }

    void handleSessions(std::atomic_bool* stop) override {
        while (!(*stop)) {
            loadNewConnections();
            setAliveConnectionsToRecieve();
            removeDeadConnections();
        }
        closeAllConnections();
    }

    ~ConnectionHandler() = default;

private:
    void onReadComplete(std::shared_ptr<Connection> &connection, const std::error_code &err, size_t read_bytes) {
        // make errors handling
        std::cout << "request async read completed" << std::endl;

        if(err){
            connection->status = ConnectionStatus::disconnected;
            return;
        }

        Request request;

        //----------------
        std::ostream oss(&connection->buff);
        std::stringstream ss;
        ss<<oss.rdbuf();
        std::string str_data = ss.str();
        str_data.erase(str_data.end() - 4, str_data.end());
        request.load(str_data);
        //----------------

        std::cout << request._table_name << std::endl;



        IWorker *worker = _wFactory.get(request, _storage);
        Request answer = worker->operate();
        delete worker;


//        if(!connection->sock.is_open()){
//            connection->_status = ConnectionStatus::disconnected;
//            return;
//        }

        connection->status = ConnectionStatus::onWrite;
        sendAnswer(connection, std::move(answer));
    }

    void onWriteComplete(std::shared_ptr<Connection> &connection, const std::error_code &err, size_t write_bytes) {
        // make errors handling
        std::cout << "async write completed" << std::endl;
        if(err){
            connection->status = ConnectionStatus::disconnected;
            return;
        }
        connection->status = ConnectionStatus::waiting;
    }

    void sendAnswer(std::shared_ptr<Connection> &connection, Request request){

        //----------------
        std::ostream oss(&connection->buff);
        request.save(oss);
        //----------------
        oss << "\r\n\r\n";
        async_write(connection->sock, connection->buff,
                    boost::bind(&ConnectionHandler::onWriteComplete, this, connection, _1, _2));
    }

    void loadNewConnections(){
        _newConnectionsMutex.lock();
        while (!_newConnections.empty()) {
            _handledConnections.push_back(std::move(_newConnections.front()));
            _newConnections.pop();
        }
        _newConnectionsMutex.unlock();
    }

    void setAliveConnectionsToRecieve(){
        for (auto& connection: _handledConnections) {
            if (connection->status == ConnectionStatus::waiting) {
                connection->status = ConnectionStatus::onRead;
                async_read_until(connection->sock, connection->buff, "\r\n\r\n",
                                 boost::bind(&ConnectionHandler::onReadComplete, this, connection, _1, _2));
            }
        }
    }

    void removeDeadConnections(){
        for (auto connection = _handledConnections.begin(); connection != _handledConnections.end();) {
            if ((*connection)->status == ConnectionStatus::disconnected) {
                connection = _handledConnections.erase(connection);
            } else {
                ++connection;
            }
        }
    }

    void closeAllConnections(){
        for (auto connection = _handledConnections.begin(); connection != _handledConnections.end();) {
            if (((*connection)->status == ConnectionStatus::waiting) || ((*connection)->status == ConnectionStatus::disconnected)) {
                (*connection)->sock.close();
                connection = _handledConnections.erase(connection);
            } else {
                ++connection;
            }
        }
    }

    std::mutex _newConnectionsMutex;
    std::vector<std::shared_ptr<Connection>> _handledConnections;
    std::queue<std::shared_ptr<Connection>> _newConnections;
    ITableStorage* _storage;
    workerFactory _wFactory;
};

#endif //MOND_DB_CONNECTIONHANDLER_H
