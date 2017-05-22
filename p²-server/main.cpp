//
//  main.cpp
//  p²-server
//
//  Created by James Carter on 2/24/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "server.h"
#include "console.h"

int main(int argc, const char * argv[]) {
    int port;
    if (argc == 2) {
        port = std::stoi(argv[1]);
    } else {
        std::cout << "Usage: " << argv[0] << " [port]" << std::endl;
        std::cout << "Defaulting to port 1722!" << std::endl;
        port = 1722;
    }
    App::Server server(port);
    return 0;
}
