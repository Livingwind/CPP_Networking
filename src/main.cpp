// Every adventure has to start somewhere. This file just happens to be my 4th...

#include <iostream>
#include "messaging/Messenger.h"
#include "server/Server.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage error: cpp_networking [messaging|server]" << std::endl;
        return 1;
    }

    if("server" == std::string(argv[1])) {
        Server server(argv[2]);
        server.start();
    }
    else if("messenger" == std::string(argv[1])) {
        Messenger messenger(argv[2], argv[3]);
        messenger.start();
    }
    return 0;
}
