//
// Created by ogrebatel on 21.11.22.
//

#ifndef INC_2022_2_MOND_BOOSTIFACE_H
#define INC_2022_2_MOND_BOOSTIFACE_H

#include <boost/asio.hpp>

struct Connection {
    boost::asio::ip::tcp::socket sock;
    boost::asio::streambuf buff; // reads the answer from the client
    std::atomic_int status;
    std::string table;
    Connection(std::shared_ptr<boost::asio::io_context> ioCtx): sock(*ioCtx){}
};

class BoostIFace {
    static boost::asio::io_context getIoContext();
    static boost::asio::ip::tcp::socket getSocket();
    static boost::asio::thread_pool getThreadPool();
};

#endif //INC_2022_2_MOND_BOOSTIFACE_H
