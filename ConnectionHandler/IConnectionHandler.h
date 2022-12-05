//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_ICONNECTIONHANDLER_H
#define MOND_DB_ICONNECTIONHANDLER_H

#include "IWorker.h"
#include "boost/asio.hpp"
#include "InternalEntities.h"

enum ConnectionStatus {
    waiting,
    onRead,
    onWrite,
    disconnected
};

struct Connection {
    Connection(boost::asio::io_context* ioContext) : sock(*ioContext), status(ConnectionStatus::waiting) {}

    boost::asio::ip::tcp::socket sock;
    boost::asio::streambuf buff; // reads the answer from the client
    std::atomic_int status;
};

class IConnectionHandler {
public:
    virtual ITableStorage* getStorage() = 0;
    virtual void listenConnections(boost::asio::io_context* ioContext, std::atomic_bool* stop) = 0;
    virtual void handleSessions(std::atomic_bool* stop) = 0;
    virtual ~IConnectionHandler() = default;
};

#endif //MOND_DB_ICONNECTIONHANDLER_H
