//
// Created by João Matos on 01/02/2023.
//

#ifndef SKYNET_TCPCLIENT_HPP
#define SKYNET_TCPCLIENT_HPP

#include <netinet/in.h>

namespace net 
{
      class Client : public Socket 
      {
      public:
            explicit Client(Protocol protocol = Protocol::TCP);
            ~Client() = default;

            int Connect(const char *host, int port);
            int Send(const char *data, size_t size);
            int Receive(char *buffer, size_t size);
      private:
            sockaddr_in address_;
      };
}

#endif //SKYNET_TCPCLIENT_HPP
