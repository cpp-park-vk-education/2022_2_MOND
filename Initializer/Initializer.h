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
    explicit Initializer(uint32_t numOfThreads): stop(false), ioContextVec(numOfThreads), storage(new TableStorage) {
        handler = new ConnectionHandler(storage);
    }

    Initializer(const Initializer& other) = delete;
    Initializer(Initializer &&other) = delete;

    Initializer& operator=(Initializer &&other) = delete;
    Initializer& operator=(const Initializer &other) = delete;

    void startDB();
    void handleCommands();
    void stopDB();

    ~Initializer();

    std::atomic_bool stop;
    std::vector<threadContext> ioContextVec;
    IConnectionHandler* handler;
    ITableStorage* storage;
    boost::thread ConnectionListener;
    boost::thread SessionHandler;
};

void Initializer::startDB() {
    ConnectionListener = boost::thread(&IConnectionHandler::listenConnections, handler, &ioContextVec, &stop);
    SessionHandler = boost::thread(&IConnectionHandler::handleSessions, handler, &stop);
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

    ConnectionListener.join();
    SessionHandler.join();
    for (auto &thread: ioContextVec) {
        thread.guard.reset();
        thread._thread.join();
    }
}

Initializer::~Initializer() {
    delete storage;
    delete handler;
}

#endif //MOND_DB_INITIALIZER_H
