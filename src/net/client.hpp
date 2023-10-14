/**
 * @file client.hpp
 * @author JoaoAJMatos
 * @brief Client abstraction
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_TCPCLIENT_HPP
#define SKYNET_TCPCLIENT_HPP

/* C++ includes */
#include <netinet/in.h>

/* Local includes */
#include "socket.hpp"

namespace net 
{
      class Client : public Socket 
      {
      public:
            explicit Client(Protocol protocol = Protocol::TCP);
            ~Client() = default;

            /** Connect to the given host and port */
            bool Connect(const char *host, int port);
            /** Send data to the connected host */
            int Send(const char *data, size_t size);
            /** Receive data from the connected host */
            int Receive(char *buffer, size_t size);
      private:
            sockaddr_in address;
      };
}

#endif //SKYNET_TCPCLIENT_HPP

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
