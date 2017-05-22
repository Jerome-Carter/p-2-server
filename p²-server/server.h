//
//  server.h
//  p²-server
//
//  Created by James Carter on 2/28/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <iostream>

#include <thread>

#include <vector>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "console.h"
#include "socket.h"

#include "client.h"
#include "id_gen.h"

//tmp
#include <unistd.h>

#define MAX_CLIENTS 10000

namespace App {
    class Server {
    private:
        int m_Port;
        datagram_socket m_Socket;
        std::vector<Client*> m_ClientList;
        unsigned long m_ClientCount;
    private:
        void run(int socket);
        static void manageClients(Server* server);
        void sendToAll(char* data);
        static void send(int socket, char* data, const Client& client);
        static void receive(int socket, Server* server);
        void filter(char* data, sockaddr_in from);
        void disconnect(unsigned long id, bool clean);
    public:
        Server(int port);
        void addClient(unsigned long id, std::string username, sockaddr_in& from);
    };
}
