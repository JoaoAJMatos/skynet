//
// Created by João Matos on 01/02/2023.
//

#include "server.hpp"

net::Server::Server(int port, Protocol protocol, int backlog) : Socket(AF_INET, 0, protocol)
{
      this->backlog_ = backlog;
      this->address_.sin_family = AF_INET;
      this->address_.sin_addr.s_addr = INADDR_ANY;
      this->address_.sin_port = htons(port);

      int result = bind(this->GetSocket(), 
                       (struct sockaddr *) &this->address_, sizeof(this->address_));

      if (result < 0) {
            throw std::runtime_error("Failed to bind socket");
      }

      result = listen(this->GetSocket(), this->backlog_);

      if (result < 0) {
            throw std::runtime_error("Failed to listen on socket");
      }
}
