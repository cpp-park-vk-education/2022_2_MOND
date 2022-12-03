//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_ICONNECTIONHANDLER_H
#define MOND_DB_ICONNECTIONHANDLER_H

#include "IWorker.h"
#include "boost/asio.hpp"
#include "InternalEntities.h"

class IConnectionHandler {
public:
    ITableStorage* storage;

    virtual void listenConnections(boost::asio::io_context* ioContext) = 0;
    virtual void handleSessions() = 0;
};

#endif //MOND_DB_ICONNECTIONHANDLER_H
