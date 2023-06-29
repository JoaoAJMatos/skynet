//
// Created by João Matos on 01/02/2023.
//

#include <cstring>
#include <arpa/inet.h>

#include "socket.hpp"

#include "client.hpp"


net::Client::Client(Protocol protocol) : Socket(AF_INET, protocol == net::Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM, 0)
{ }

int net::Client::Connect(const char *host, int port) 
{
      this->address_.sin_family = AF_INET;
      this->address_.sin_port = htons(port);
      this->address_.sin_addr.s_addr = inet_addr(host);
      memset(this->address_.sin_zero, '\0', sizeof(this->address_.sin_zero));
      inet_pton(AF_INET, host, &this->address_.sin_addr);

      int result = connect(this->GetSocket(), 
                          (struct sockaddr *) &this->address_, sizeof(this->address_));
      return result;
}

int net::Client::Send(const char *data, size_t size) 
{
      int result = send(this->GetSocket(), data, size, 0);
      return result;
}

int net::Client::Receive(char *buffer, size_t size) 
{
      int result = recv(this->GetSocket(), buffer, size, 0);
      return result;
}

