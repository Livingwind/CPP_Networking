//
// Created by maat on 7/27/18.
// Explaining the abstract using only it's parts is the basis of communication.
//

#include <iostream>
#include "Messenger.h"
#include <iostream>

using boost::asio::ip::tcp;

Messenger::Messenger(const std::string& address, const std::string& port)
  : io_context(), socket(io_context) {

  tcp::resolver resolver(io_context);
  auto endpoints = resolver.resolve(address, port);

  boost::asio::async_connect(socket, endpoints,
      [this](boost::system::error_code error_code, tcp::endpoint){
    if(!error_code) {
      std::cout << "Connected successfully" << std::endl;
    } else {
      std::cerr << "Could not connect to server." << std::endl;
    }
  });
}

void Messenger::start() {
  io_context.run();
}