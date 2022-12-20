//
// Created by ogrebatel on 03.12.22.
//

#ifndef MOND_DB_INITIALIZER_H
#define MOND_DB_INITIALIZER_H

#include <pthread.h>

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

    Initializer(const Initializer& other) = delete;
    Initializer(Initializer &&other) = delete;

    Initializer& operator=(Initializer &&other) = delete;
    Initializer& operator=(const Initializer &other) = delete;

    void startDB(uint32_t numOfThreads);
    void handleCommands();
    void stopDB();

    ~Initializer();

    std::atomic_bool stop;
    boost::asio::io_context ioContext;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> guard;
    IConnectionHandler* handler;
    ITableStorage* storage;
    boost::thread_group threadGroup;
    boost::thread ConnectionListener;
    boost::thread SessionHandler;
};

void Initializer::startDB(uint32_t numOfThreads) {

    ConnectionListener = boost::thread(&IConnectionHandler::listenConnections, handler, &ioContext, &stop);
    SessionHandler = boost::thread(&IConnectionHandler::handleSessions, handler, &stop);

    std::cout << "creating server with " << numOfThreads << " threads" << std::endl;

    for (uint32_t i = 0; i < numOfThreads; ++i) {
        threadGroup.create_thread(
                boost::bind(&boost::asio::io_service::run, &ioContext)
        );
    }
}

void Initializer::handleCommands() {
    std::string command;
    while (true){
        std::cin >> command;
        if (command == "stop")
            return;
    }
}

void Initializer::stopDB() {
    stop = true;
    guard.reset();
    ConnectionListener.join();
    SessionHandler.join();
    threadGroup.join_all();
}

Initializer::~Initializer() {
    delete storage;
    delete handler;
}

#endif //MOND_DB_INITIALIZER_H
