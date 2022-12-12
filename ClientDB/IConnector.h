#ifndef MOND_DB_ICONNECTOR_H
#define MOND_DB_ICONNECTOR_H

#include <boost/asio.hpp>

class IConnector {
public:
    virtual void Connect(const std::string &address, const uint16_t &port) = 0;
    virtual void Disconnect() = 0;

    virtual std::size_t Write(boost::asio::streambuf & buff) = 0;
    virtual std::size_t Read(boost::asio::streambuf & buff) = 0;

    virtual ~IConnector() = default;
};

#endif//MOND_DB_ICONNECTOR_H
