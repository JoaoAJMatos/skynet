//
// Created by João Matos on 01/02/2023.
//

#include "server.hpp"

net::Server::Server(int port, Protocol protocol, int backlog) : Socket(AF_INET, 0, protocol) {
      this->backlog = backlog;
      this->address.sin_family = AF_INET;
      this->address.sin_addr.s_addr = INADDR_ANY;
      this->address.sin_port = htons(port);

      int result = bind(this->GetSocket(), 
                       (struct sockaddr *) &this->address, sizeof(this->address));

      if (result < 0)
            throw std::runtime_error("Failed to bind socket");

      result = listen(this->GetSocket(), this->backlog);

      if (result < 0)
            throw std::runtime_error("Failed to listen on socket");
}

net::Server::~Server() {
	this->Stop();
}

/**
 * @brief Starts the server loop.
 *        The server loop and logic must be defined by
 *        overriding the Launch and Accept methods.
 */
void net::Server::Run() {
	this->Launch();
	while (!this->shouldStop)
	      this->Accept();
}

/**
 * @brief Sets the should_stop flag to true.
 *        Stops the server loop.
 */
void net::Server::Stop() {
	this->shouldStop = true;
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
