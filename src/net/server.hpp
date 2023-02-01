//
// Created by João Matos on 01/02/2023.
//

#ifndef SKYNET_SERVER_HPP
#define SKYNET_SERVER_HPP

#include "common.hpp"
#include "socket.hpp"

namespace net {
    class CServer : public CSocket {
    public:
        CServer(int port, Protocol protocol = NET_TCP, int max_clients = 10);    // Protocol maps to the socket type
        ~CServer();

        virtual void launch() = 0;
    private:
        sockaddr_in m_server_address;
        int m_max_clients;

        virtual void accept() = 0;
        virtual void handle() = 0;
    };
} // namespace Net

#endif //SKYNET_SERVER_HPP
