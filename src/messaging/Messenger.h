//
// Created by maat on 7/27/18.
//

#ifndef CPP_NETWORKING_MESSAGING_MAIN_H
#define CPP_NETWORKING_MESSAGING_MAIN_H

#include <boost/asio.hpp>

class Messenger {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket;

 public:
    Messenger(const std::string& address, const std::string& port);
    ~Messenger() noexcept = default;

    void start();

    Messenger(const Messenger&) = delete;
    Messenger operator=(const Messenger&) = delete;

};

#endif //CPP_NETWORKING_MESSAGING_MAIN_H
