/**
 * @file server.hpp
 * @author JoaoAJMatos
 * @brief Server abstraction
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_SERVER_HPP
#define SKYNET_SERVER_HPP

#include <netinet/in.h>
#include <stdexcept>

#include "socket.hpp"

namespace net
{
      class Server : public Socket 
      {
      public:
            Server(int port, Protocol protocol = Protocol::TCP, int backlog = 10);
            ~Server();
            
            void Run();
            void Stop();
      private:
            sockaddr_in address_;
            int backlog_;

            virtual void Launch() = 0;
            virtual void Accept() = 0;
            virtual void Handle() = 0;
      };
}


#endif //SKYNET_SERVER_HPP


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
