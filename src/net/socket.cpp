//
// Created by João Matos on 01/02/2023.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <cassert>

#include "socket.hpp"


net::Socket::Socket(int domain, int type, int protocol) 
{
    assert(domain == AF_INET || domain == AF_INET6);
    assert(type == SOCK_STREAM || type == SOCK_DGRAM);

    int socket_fd = socket(domain, type, protocol);
    if (socket_fd < 0) {
        throw std::runtime_error("Failed to create socket");
    }
    this->socket_ = socket_fd;
}

net::Socket::Socket(int domain, int type, net::Protocol protocol)
{
      int protocol_int = static_cast<int>(protocol);
      Socket(domain, type, protocol_int);
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

void net::Socket::SetNonBlocking(const bool flag) const 
{
      int flags = fcntl(this->socket_, F_GETFL, 0);
      if (flags == -1) {
            throw std::runtime_error("Failed to get socket flags");
      }

      flags = flag ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
      int result = fcntl(this->socket_, F_SETFL, flags);
      if (result == -1) {
            throw std::runtime_error("Failed to set socket flags");
      }
}

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
