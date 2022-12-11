#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "InternalEntities.h"



boost::asio::io_service service;

boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 8001);
size_t read_complete(char * buf, const std::error_code & err, size_t bytes)
{
    if ( err) return 0;
    bool found = std::find(buf, buf + bytes, '\n') < buf + bytes;
    // we read one-by-one until we get to enter, no buffering
    return found ? 0 : 1;
}
void sync_echo()
{

    Request request;
    request._type = requestType::CREATE_TABLE;
    request._table_name = "myFirstTable";
    request._status = Status::NOTHING;

    boost::asio::streambuf buff;

    std::ostream oss(&buff);
    request.save(oss);

    boost::asio::ip::tcp::socket sock(service);
    sock.connect(ep);

    oss << "\r\n\r\n";
    boost::asio::write(sock, buff);

    boost::asio::read_until(sock, buff, "\r\n\r\n");
//"\r\n\r\n"
    Request answer;

    //----------------
    std::ostream answer_oss(&buff);
    std::stringstream ss;
    ss<<oss.rdbuf();
    std::string str_data = ss.str();
    request.load(str_data);

    if(request._status == Status::OK){
        std::cout << "success!" << std::endl;
    }
    sock.close();
}
int main(int argc, char* argv[])
{
    sync_echo();
}
