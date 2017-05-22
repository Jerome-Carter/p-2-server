//
//  server.cpp
//  p²-server
//
//  Created by James Carter on 2/28/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "server.h"

namespace App {
    Server::Server(int port) : m_Port(port), m_ClientCount(0) {
        m_ClientList.resize(1000);
        if ((m_Socket.file_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
            perror("Failed to create socket");
            return;
        }
        Console::out("UDP socket created");
        memset((void*)&m_Socket.address, 0, sizeof(m_Socket.address));
        m_Socket.address.sin_family = AF_INET;
        m_Socket.address.sin_addr.s_addr = inet_addr("127.0.0.1");
        m_Socket.address.sin_port = htons(port);
        if ((bind(m_Socket.file_descriptor, (struct sockaddr*)&m_Socket.address, sizeof(m_Socket.address))) < 0) {
            perror("Failed to bind socket");
            return;
        }
        Console::out("UDP socket bound");
        unsigned int addr_length = sizeof(m_Socket.address);
        if (getsockname(m_Socket.file_descriptor, (struct sockaddr *)&m_Socket.address, &addr_length) < 0) {
            perror("Failed to retreive socket name");
            return;
        }
        std::cout << "Server at " << inet_ntoa(m_Socket.address.sin_addr) << " started on port " << ntohs(m_Socket.address.sin_port) << std::endl;
        Console::out("Waiting for connection...");
        run(m_Socket.file_descriptor);
    }
    void Server::addClient(unsigned long id, std::string username, sockaddr_in& from) {
        m_ClientList.at(id) = new Client(id, username, from);
        m_ClientCount++;
        Client client = *m_ClientList.at(id);
        std::cout << "New User(" << "[" << m_ClientCount << "]" << client.getID() << "): " << client.getIp() << ":" << client.getPort() << " as " << client.getUsername();
    }
    void Server::run(int socket) {
        std::thread ManageClients(manageClients, this);
        std::thread Receive(receive, socket, this);
        ManageClients.join();
        Receive.join();
    }
    void Server::manageClients(Server* server) {
        bool running = true;
        while (running) {
            
        }
    }
    void Server::sendToAll(char* data) {
        for (int i = 0; i < m_ClientList.size(); i++) {
            if (m_ClientList.at(i) != NULL) {
                send(m_Socket.file_descriptor, data, *m_ClientList.at(i));
            }
        }
    }
    void Server::send(int socket, char* data, const Client& client) {
        std::thread tSend([socket, data, client] () {
            char* msg = (char*)std::string(std::string(data) + "|0").c_str();
            long bytes_sent;
            unsigned long len = std::strlen(msg);
            const sockaddr_in &re = client.getClient();
            if ((bytes_sent = sendto(socket, msg, len, 0, (struct sockaddr*)&re, sizeof(struct sockaddr))) < 0) {
                perror("Failed to send data");
            } else {
                //std::cout << std::string(msg) << " sent to " << client.getIp() << ":" << client.getPort() << std::endl;
            }
        });
        tSend.detach();
    }
    void Server::receive(int socket, Server* server) {
        bool running = true;
        while (running) {
            char data[1024];
            long bytes_recved;
            sockaddr_in from;
            socklen_t addr_len = sizeof(from);
            if ((bytes_recved = recvfrom(socket, data, sizeof(data), 0, (struct sockaddr*)&from, &addr_len)) < 0) {
                perror("Failed to receive data");
            }
            //std::cout << "Recieved data: " << "\"" << data << "\"" << " from " << inet_ntoa(from.sin_addr)/* << "(" << hostp->h_name << ")"*/ << " on port " << std::to_string(ntohs(from.sin_port)) << std::endl;
            if (strlen(data) != 2) {
                server->filter(data, from);
                bzero(data, 1024);
            }
            //server->addClient(1, from);
        }
    }
    char* extract_between(const char *str, const char *p1, const char *p2) {
        const char *i1 = strstr(str, p1);
        if (i1 != NULL) {
            const size_t pl1 = strlen(p1);
            const char *i2 = strstr(i1 + pl1, p2);
            if (p2 != NULL) {
                /* Found both markers, extract text. */
                const size_t mlen = i2 - (i1 + pl1);
                char* ret = (char*)malloc(mlen + 1);
                if (ret != NULL) {
                    memcpy(ret, i1 + pl1, mlen);
                    ret[mlen] = '\0';
                    return ret;
                }
            }
        }
        return (char*)std::string("").c_str();
    }
    void Server::filter(char* data, sockaddr_in from) {
        std::string out;
        std::string connection(";(CONNECTION):");
        std::string exit(";(EXIT):");
        if (std::string(data).compare(0, connection.length(), connection) == 0) {
            id_gen gen;
            unsigned long id = gen.getIdentifier();
            if (id != LIMIT + 1) {
                std::string message(extract_between((const char*)data, connection.c_str(), "|0"));
                addClient(id, message, from);
                std::string conf_conn = ";(CONFIRM):";
                conf_conn.append(std::to_string(id));
                send(m_Socket.file_descriptor, (char*)conf_conn.c_str(), (const Client)*m_ClientList.at(id));
                Console::out(out);
            } else {
                Console::out("Client rejected!!!");
            }
        } else if (std::string(data).compare(0, exit.length(), exit) == 0) {
            unsigned long id = std::stoul(extract_between((const char*)data, exit.c_str(), "|0"));
            disconnect(id, true);
        } else {
            char* out = extract_between((const char*)data, "", "|0");
            Console::out(out);
            sendToAll(out);
        }
    }
    void Server::disconnect(unsigned long id, bool clean) {
        if (m_ClientList.at(id) != NULL) {
            Console::out(m_ClientList.at(id)->getUsername() + "(" + std::to_string(m_ClientList.at(id)->getID()) + ")" + " has exited (Clean = " + std::to_string(clean) + ")");
            m_ClientList.at(id) = NULL;
            m_ClientCount--;
        }
    }
}
