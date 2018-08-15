//
// Created by christopher on 8/9/18.
//

#ifndef CPP_NETWORKING_SERVER_CLASS_H
#define CPP_NETWORKING_SERVER_CLASS_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server {
    boost::asio::io_context io_context;
    boost::asio::signal_set termination_signals;
    tcp::acceptor acceptor;

public:
    Server(std::string port);
    ~Server() noexcept;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void start();
    void stop();

private:
    void register_accept();

};


#endif //CPP_NETWORKING_SERVER_CLASS_H
