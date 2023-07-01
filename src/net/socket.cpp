//
// Created by João Matos on 01/02/2023.
//

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#define close(sockfd) closesocket(sockfd)
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif // defined(_WIN32) || defined(_WIN64)

#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <cassert>

#include "socket.hpp"


net::Socket::Socket(int domain, int type, int protocol) 
{
    assert(domain == AF_INET || domain == AF_INET6);
    assert(type == SOCK_STREAM || type == SOCK_DGRAM);

#if defined(_WIN32) || defined(_WIN64)
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
	    throw std::runtime_error("Failed to initialize Winsock");
    }
#endif // defined(_WIN32) || defined(_WIN64)

    this->socket_ = socket(domain, type, protocol);
    if (this->socket_ < 0) {
        throw std::runtime_error("Failed to create socket");
    }
}

net::Socket::Socket(int domain, int type, net::Protocol protocol)
{
	assert(domain == AF_INET || domain == AF_INET6);
	assert(type == SOCK_STREAM || type == SOCK_DGRAM);
      
#if defined(_WIN32) || defined(_WIN64)
      WSADATA wsa_data;
      int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
      if (result != 0) {
            throw std::runtime_error("Failed to initialize Winsock");
      }
#endif // defined(_WIN32) || defined(_WIN64)

      int protocol_int = static_cast<int>(protocol);
	this->socket_ = socket(domain, type, protocol_int);
	if (this->socket_ < 0) {
		throw std::runtime_error("Failed to create socket");
	}
}

net::Socket::~Socket() 
{ 
      close(this->socket_); 
}

void net::Socket::Close() const 
{ 
      close(this->socket_); 
}

int net::Socket::IsValid() const 
{ 
      return this->socket_ != -1; 
}

/**
 * @brief Set the socket to non-blocking mode
 * @param flag | True, set to non-blocking.
 *             | False, set to blocking.
 */
void net::Socket::SetNonBlocking(const bool flag) const 
{
#if defined(_WIN32) || defined(_WIN64)
      u_long mode = flag ? 1 : 0;
      int result = ioctlsocket(this->socket_, FIONBIO, &mode);
	if (result != NO_ERROR) {
            throw std::runtime_error("Failed to set socket flags");
	}
#else
      int flags = fcntl(this->socket_, F_GETFL, 0);
      if (flags == -1) {
            throw std::runtime_error("Failed to get socket flags");
      }

      flags = flag ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
      int result = fcntl(this->socket_, F_SETFL, flags);
      if (result == -1) {
            throw std::runtime_error("Failed to set socket flags");
      }
#endif // defined(_WIN32) || defined(_WIN64)
}

/**
 * @brief Get the remote address of the connected peer
 * @return std::string | The IPv4 address of the peer
 */
std::string net::Socket::GetRemoteAddress() const
{
      struct sockaddr_in addr;
      socklen_t addr_size = sizeof(struct sockaddr_in);
      int res = getpeername(this->socket_, (struct sockaddr *)&addr, &addr_size);
      if (res == -1) {
            throw std::runtime_error("Failed to get peer name");
      }
      char ipstr[INET_ADDRSTRLEN] = {'\0'};
      inet_ntop(AF_INET, &addr.sin_addr, ipstr, sizeof(ipstr));
      return std::string(ipstr);
}

/**
 * @brief Get the remote port of the connected peer
 * @return uint16_t | The port of the peer
 */
uint16_t net::Socket::GetRemotePort() const
{
      struct sockaddr_in addr;
      socklen_t addr_size = sizeof(struct sockaddr_in);
      int res = getpeername(this->socket_, (struct sockaddr *)&addr, &addr_size);
      if (res == -1) {
            throw std::runtime_error("Failed to get peer name");
      }
      return ntohs(addr.sin_port);
}

int net::Socket::GetSocket() const
{
      return this->socket_;
}


// MIT License
// 
// Copyright (c) 2023 João Matos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
