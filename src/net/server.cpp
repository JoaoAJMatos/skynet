//
// Created by João Matos on 01/02/2023.
//

#include "server.hpp"

net::CServer::CServer(int port, Protocol protocol, int max_clients)
             : CSocket(AF_INET, protocol == NET_TCP ? SOCK_STREAM : SOCK_DGRAM, 0)
{
    this->m_max_clients = max_clients;
    this->m_server_address.sin_family = AF_INET;
    this->m_server_address.sin_addr.s_addr = INADDR_ANY;
    this->m_server_address.sin_port = htons(port);

    int result = bind(this->get_socket(), (struct sockaddr *) &this->m_server_address, sizeof(this->m_server_address));
    if (result == NET_ERROR) {
        throw std::runtime_error("Failed to bind socket");
    }

    if (protocol == NET_TCP) {
        result = listen(this->get_socket(), this->m_max_clients);
        if (result == NET_ERROR) {
            throw std::runtime_error("Failed to listen on socket");
        }
    }
}