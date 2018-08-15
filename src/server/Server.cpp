//
// Created by christopher on 8/9/18.
//

#include "Server.h"
#include <iostream>

// Constructor
/**
 * Construct a server object that can accept incoming connections on the
 *  specified port.
 *
 * @param port
 */
Server::Server(const std::string port)
  : io_context(),
  acceptor(io_context),
  termination_signals(io_context) {

  /**
   *  Add ICP signals that we're interested in to the signal set.
   *  (1) interrupt (Ctrl-C)
   *  (2) terminate
   *  (3) QUIT (Ctrl-\)
   *
   *  (4) Await one of the signals and begin stopping the server.
   *    >>The use of ICP signals are inherently thread unsafe<<
   *  (5) Start the acceptor listening on the given port. This was mostly taken from the boost::asio http server
   *    example page.
   *  (6) Register what to do when the server accepts a connection.
   */

  termination_signals.add(SIGINT);  // (1)
  termination_signals.add(SIGTERM); // (2)
  termination_signals.add(SIGQUIT); // (3)

  termination_signals.async_wait(
      [this](boost::system::error_code error_code, int) {
        std::cout << "Intercepted signal [" << error_code << "]" << std::endl;
        stop();
      }); // (4)

  tcp::resolver resolver(io_context);
  tcp::endpoint endpoint = *resolver.resolve("0.0.0.0", port).begin();
  acceptor.open(endpoint.protocol());
  acceptor.bind(endpoint);
  acceptor.listen();  // (5)

  register_accept();  // (6)
}

Server::~Server() {
  if (acceptor.is_open()) {
    stop();
  }
}

/**
 * Create and run the io_context in a seperate thread managed internally by the Server object.
 */
void Server::start() {
  std::cout << "Starting server on [" << acceptor.local_endpoint() << "]..." << std::endl;
  io_context.run();
};

/**
 * Close the TCP acceptor and safely join the io_context thread.
 */
void Server::stop() {
  std::cout << "Stopping server..." << std::endl;
  acceptor.close();
}

void Server::register_accept() {
  acceptor.async_accept(
      [this](boost::system::error_code error_code, tcp::socket socket) {
        if (!acceptor.is_open()) {
          return;
        }
        if (!error_code) {
            std::cout << "Successfully connected..." << std::endl;
        } else {
          std::cerr << "Error accepting connection. Error code: " << error_code << std::endl;
        }

        register_accept();
      });
}
