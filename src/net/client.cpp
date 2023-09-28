//
// Created by João Matos on 01/02/2023.
//

#include <cstring>
#include <arpa/inet.h>

#include "client.hpp"


net::Client::Client(Protocol protocol) : Socket(AF_INET, protocol == net::Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM, 0)
{ }

int net::Client::Connect(const char *host, int port) {
      this->address_.sin_family = AF_INET;
      this->address_.sin_port = htons(port);
      this->address_.sin_addr.s_addr = inet_addr(host);
      memset(this->address_.sin_zero, '\0', sizeof(this->address_.sin_zero));
      inet_pton(AF_INET, host, &this->address_.sin_addr);

      int result = connect(this->GetSocket(), 
                          (struct sockaddr *) &this->address_, sizeof(this->address_));
      return result;
}

int net::Client::Send(const char *data, size_t size) {
      int result = send(this->GetSocket(), data, size, 0);
      return result;
}

int net::Client::Receive(char *buffer, size_t size) {
      int result = recv(this->GetSocket(), buffer, size, 0);
      return result;
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
