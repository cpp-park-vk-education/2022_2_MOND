//
// Created by ogrebatel on 21.11.22.
//

#ifndef MOND_DB_CONNECTIONHANDLER_H
#define MOND_DB_CONNECTIONHANDLER_H

#include "InternalEntities.h"
#include "ConnectionWorker.hpp"

class IConnectionHandler{
public:
    virtual void listenConnections() = 0;
    virtual void handleSessions(std::shared_ptr<boost::asio::io_context> ioCtx) = 0;
    virtual void distribute(std::shared_ptr<Connection> conn) = 0;
};

class ConnectionHandler : public IConnectionHandler{
public:

    void listenConnections() override {

    }

    void handleSessions(std::shared_ptr<boost::asio::io_context> ioCtx) override {

    }

    void distribute(std::shared_ptr<Connection> conn) override {

    }
private:
    std::vector<std::shared_ptr<Connection>> connections;
    IController controller;
    workerFactory wFactory;
    ISerializer serializer;
};



#endif //MOND_DB_CONNECTIONHANDLER_H
