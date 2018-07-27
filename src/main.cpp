// Every adventure has to start somewhere. This file just happens to be my 4th...

#include <iostream>
#include "messaging/messaging_main.h"
#include "server/server_main.h"

int main() {
    messaging::messaging_test();
    server::server_test();
    return 0;
}