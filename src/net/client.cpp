//
// Created by João Matos on 01/02/2023.
//

#include "client.hpp"

net::CClient::CClient(Protocol protocol) : CSocket(AF_INET, protocol == NET_TCP ? SOCK_STREAM : SOCK_DGRAM, 0) {}

net::CClient::~CClient() = default;

net::ErrorCode net::CClient::Connect(const char *host, int port) {
    this->m_server_address.sin_family = AF_INET;
    this->m_server_address.sin_port = htons(port);
    this->m_server_address.sin_addr.s_addr = inet_addr(host);
    memset(this->m_server_address.sin_zero, '\0', sizeof(this->m_server_address.sin_zero));
    inet_pton(AF_INET, host, &this->m_server_address.sin_addr);

    int result = connect(this->get_socket(), (struct sockaddr *) &this->m_server_address, sizeof(this->m_server_address));
    if (result == NET_ERROR) {
        return NET_ERROR;
    }

    return NET_OK;
}

net::ErrorCode net::CClient::Send(const char *data, size_t size) {
    int result = send(this->get_socket(), data, size, 0);
    if (result == NET_ERROR) {
        return NET_ERROR;
    }

    return NET_OK;
}

net::ErrorCode net::CClient::Receive(char *buffer, size_t size) {
    int result = recv(this->get_socket(), buffer, size, 0);
    if (result == NET_ERROR) {
        return NET_ERROR;
    }

    return NET_OK;
}

