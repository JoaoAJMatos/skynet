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

/** C++ includes */
#include <stdexcept>
#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif // defined(_WIN32) || defined(_WIN64)

/** Local includes */
#include "socket.hpp"


namespace net
{
      /** Default backlog size */
      constexpr int DEFAULT_BACKLOG = 10;

      class Server : public Socket 
      {
      public:
            Server(int port, Protocol protocol = Protocol::TCP, int backlog = DEFAULT_BACKLOG);
            ~Server();

            /** Starts the server loop */
            void Run();
            /** Stops the server loop */
            void Stop();
            /** Checks if the server backlog is full */
            bool BacklogFull();

            /** Getters */
            [[nodiscard]] int GetPort() const { return ntohs(address.sin_port); }
            [[nodiscard]] int GetBacklog() const { return backlog; }

            /** Setters */
            void SetPort(int port) { address.sin_port = htons(port); }
            void SetBacklog(int backlog) { this->backlog = backlog; }
      private:
            sockaddr_in address;
            int backlog;

            /** VIRTUAL METHODS */
            /** Launch must implement the server bootstrap procedure */
            virtual void Launch() = 0;
            /** Accept should accept new connections */
            virtual void Accept() = 0;
            /** Shutdown should implement the shutdown procesure of the server */
            virtual void Shutdown() = 0;
      protected:
		bool shouldStop;
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
