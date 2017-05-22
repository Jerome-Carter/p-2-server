//
//  client.h
//  p²-server
//
//  Created by James Carter on 3/1/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <string>
#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace App {
    struct Client {
    private:
        const unsigned long ID;
        int attempt = 0;
        std::string ip;
        unsigned short port;
        std::string hostname;
        const std::string username;
        const struct sockaddr_in client;
    public:
        Client(const unsigned long ID, std::string username, sockaddr_in client);
        inline unsigned long getID() const { return ID; }
        inline int getAttempt() const { return attempt; }
        inline std::string getIp() const { return ip; }
        inline unsigned short getPort() const { return port; }
        inline std::string getHostname() const { return hostname; }
        inline std::string getUsername() const { return username; }
        inline sockaddr_in getClient() const { return client; }
    };
}
