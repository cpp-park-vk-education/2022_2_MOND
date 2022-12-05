//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_CONNECTIONHANDLER_H
#define MOND_DB_CONNECTIONHANDLER_H

#include <queue>
#include "IConnectionHandler.h"
#include <boost/bind.hpp>
#include "ISerializer.h"
#include "Serializer.h"


class ConnectionHandler : public IConnectionHandler {
public:
    explicit ConnectionHandler(ITableStorage* storage): storage(storage){}

    ITableStorage* getStorage() override {
        return storage;
    }

    void listenConnections(boost::asio::io_context *ioContext, std::atomic_bool* stop) override {
        boost::asio::ip::tcp::acceptor acceptor(*ioContext,
                                                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001));
        while (!(*stop)) {
            std::shared_ptr<Connection> conn = std::make_shared<Connection>(ioContext);
            acceptor.accept(conn->sock);
            newConnectionsMutex.lock();
            newConnections.push(std::move(conn));
            newConnectionsMutex.unlock();
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


    void onRead(std::shared_ptr<Connection> &connection, const std::error_code &err, size_t read_bytes) {

        // make errors handling
        if(err){
            connection->status = ConnectionStatus::disconnected;
            return;
        }

        std::istream in(&connection->buff);
        std::string msg;
        std::getline(in, msg);

//        std::cout << msg;

        ISerializer* serializer = new Serializer;
        Request request /*= serializer->Unmarshal(msg.c_str())*/; //?
        IWorker *worker = wFactory.get(request, storage);
        Request answer = worker->operate();
        delete worker;

//        if(!connection->sock.is_open()){
//            connection->status = ConnectionStatus::disconnected;
//            return;
//        }

        connection->status = ConnectionStatus::onWrite;
        sendAnswer(connection, std::move(request));
    }

    void onWrite(std::shared_ptr<Connection> &connection, const std::error_code &err, size_t write_bytes) {
        // make errors handling
        if(err){
            connection->status = ConnectionStatus::disconnected;
            return;
        }
        connection->status = ConnectionStatus::waiting;
    }

    void sendAnswer(std::shared_ptr<Connection> &connection, Request request){

        async_write(connection->sock, connection->buff,
                    boost::bind(&ConnectionHandler::onWrite, this, connection, _1, _2));
    }

    void loadNewConnections(){
        newConnectionsMutex.lock();
        while (!newConnections.empty()) {
            handledConnections.push_back(std::move(newConnections.front()));
            newConnections.pop();
        }
        newConnectionsMutex.unlock();
    }

    void setAliveConnectionsToRecieve(){
        for (auto& connection: handledConnections) {
            if (connection->status == ConnectionStatus::waiting) {
                connection->status = ConnectionStatus::onRead;
                async_read_until(connection->sock, connection->buff, '\n',
                                 boost::bind(&ConnectionHandler::onRead, this, connection, _1, _2));
            }
        }
    }

    void removeDeadConnections(){
        for (auto connection = handledConnections.begin(); connection != handledConnections.end();) {
            if ((*connection)->status == ConnectionStatus::disconnected) {
                connection = handledConnections.erase(connection);
            } else {
                ++connection;
            }
        }
    }

    void closeAllConnections(){
        for (auto connection = handledConnections.begin(); connection != handledConnections.end();) {
            if (((*connection)->status == ConnectionStatus::waiting) || ((*connection)->status == ConnectionStatus::disconnected)) {
                (*connection)->sock.close();
                connection = handledConnections.erase(connection);
            } else {
                ++connection;
            }
        }
    }

    std::mutex newConnectionsMutex;
    std::vector<std::shared_ptr<Connection>> handledConnections;
    std::queue<std::shared_ptr<Connection>> newConnections;
    ITableStorage* storage;
    workerFactory wFactory;


};

#endif //MOND_DB_CONNECTIONHANDLER_H
