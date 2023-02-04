//
// Created by João Matos on 01/02/2023.
//

#ifndef SKYNET_TCPCLIENT_HPP
#define SKYNET_TCPCLIENT_HPP

#include "common.hpp"
#include "socket.hpp"

namespace net {
    class CClient : public CSocket {
    public:
        explicit CClient(Protocol protocol = NET_TCP);    // Protocol maps to the socket type
        ~CClient();

        ErrorCode Connect(const char *host, int port);
        ErrorCode Send(const char *data, size_t size);
        ErrorCode Receive(char *buffer, size_t size);
    private:
        sockaddr_in m_server_address{};
    };
} // namespace Net

#endif //SKYNET_TCPCLIENT_HPP
