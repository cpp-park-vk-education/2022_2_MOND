#ifndef MOND_DB_CONNECTOR_H
#define MOND_DB_CONNECTOR_H

#include "IConnector.h"

class Connector : public IConnector {
    void Connect(const std::string &address, const uint16_t &port) override;
    void Disconnect() override;

    std::size_t Write(boost::asio::streambuf & buff) override;
    std::size_t Read(boost::asio::streambuf & buff) override;

private:
    boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep;
    boost::asio::ip::tcp::socket sock = boost::asio::ip::tcp::socket(service);
};

void Connector::Connect(const std::string &address, const uint16_t &port) {
    ep.address(boost::asio::ip::address::from_string(address));
    ep.port(port);

    sock.connect(ep);
}

void Connector::Disconnect() {
    sock.close();
}

std::size_t Connector::Write(boost::asio::streambuf &buff) {
    return boost::asio::write(sock, buff);
}
std::size_t Connector::Read(boost::asio::streambuf &buff) {
    return boost::asio::read_until(sock, buff, "\r\n\r\n");
}
#endif//  MOND_DB_CONNECTOR_H
