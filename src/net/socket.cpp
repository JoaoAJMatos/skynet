//
// Created by João Matos on 01/02/2023.
//

#include "socket.hpp"

net::CSocket::CSocket(int domain, int type, int protocol) {
    assert(domain == AF_INET || domain == AF_INET6);
    assert(type == SOCK_STREAM || type == SOCK_DGRAM);

    int socket_fd = socket(domain, type, protocol);
    if (socket_fd < 0) {
        throw std::runtime_error("Failed to create socket");
    }

#ifdef _WIN32
    WORD wVersionRequired = MAKEWORD(2, 2);
    int iResult = WSAStartup(wVersionRequired, &wsa);
    if (iResult != 0) throw std::runtime_error("Failed to initialize Winsock");
#endif

    this->m_socket = socket_fd;
}

net::CSocket::~CSocket() {
    close(this->m_socket);
}

void net::CSocket::set_non_blocking(const bool non_blocking) const {
    int flags = fcntl(this->m_socket, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("Failed to get socket flags");
    }

    flags = non_blocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    int result = fcntl(this->m_socket, F_SETFL, flags);
    if (result == -1) {
        throw std::runtime_error("Failed to set socket flags");
    }
}
