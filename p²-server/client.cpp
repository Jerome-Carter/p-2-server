//
//  Client.cpp
//  p²-server
//
//  Created by James Carter on 3/1/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "client.h"

namespace App {
    Client::Client(const unsigned long ID, std::string username, sockaddr_in client) : ID(ID), username(username), client(client) {
        ip = inet_ntoa(client.sin_addr);
        port = ntohs(client.sin_port);
        struct hostent* hostp = gethostbyaddr((const char *)&client.sin_addr.s_addr, sizeof(client.sin_addr.s_addr), AF_INET);
        hostname = hostp->h_name;
    };
}
