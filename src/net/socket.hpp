/**
 * @file   socket.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains the implementation of the Socket abstraction.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_SOCKET_HPP
#define SKYNET_SOCKET_HPP

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <winerror.h>
#include <tchar.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <unistd.h>
#include <iostream>
#include <fcntl.h>

#include "common.hpp"

namespace net {
    class CSocket {
    public:
        CSocket(int domain, int type, int protocol = 0);
        ~CSocket();

        void set_non_blocking(const bool non_blocking) const;
        bool is_valid() const { return m_socket != NET_ERROR; }

        [[nodiscard]] int get_socket() const { return m_socket; }
        char* get_last_error() const { return m_last_error; }

    private:
        int m_socket;
        char* m_last_error{};

#if defined(_WIN32)
        WSAData m_wsa_data;
#endif
    };
} // namespace net


#endif //SKYNET_SOCKET_HPP
