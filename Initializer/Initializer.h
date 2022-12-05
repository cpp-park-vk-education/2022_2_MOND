//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_INITIALIZER_H
#define MOND_DB_INITIALIZER_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "ITableStorage.h"
#include "TableStorage.h"

#include "IConnectionHandler.h"
#include "ConnectionHandler.h"


class Initializer {
public:
    explicit Initializer(): stop(false), guard(boost::asio::make_work_guard(ioContext)), storage(new TableStorage) {
        handler = new ConnectionHandler(storage);
    }

    void startDB(uint32_t numOfThreads){

        ConnectionListener = boost::thread(&IConnectionHandler::listenConnections, handler, &ioContext, &stop);
        SessionHandler = boost::thread(&IConnectionHandler::handleSessions, handler, &stop);

        for (uint32_t i = 0; i < numOfThreads; ++i) {
            threadGroup.create_thread(
                    boost::bind(&boost::asio::io_service::run, &ioContext)
            );
        }
    }

    void stopDB(){ //?
        stop = true;
        guard.reset();
        ConnectionListener.join();
        SessionHandler.join();
        threadGroup.join_all();
    }

    ~Initializer(){
        delete storage;
        delete handler;
    }

    std::atomic_bool stop;
    boost::asio::io_context ioContext;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> guard;
    IConnectionHandler* handler;
    ITableStorage* storage;
    boost::thread_group threadGroup;
    boost::thread ConnectionListener;
    boost::thread SessionHandler;
};

#endif //MOND_DB_INITIALIZER_H
