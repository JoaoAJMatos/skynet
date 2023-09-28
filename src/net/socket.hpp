/**
 * @file   socket.hpp
 * @author JoaoAJMatos
 * @brief  Socket wrapper
 * @date   2023-02-01
 * 
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_SOCKET_HPP
#define SKYNET_SOCKET_HPP

#include <string>

#include "net.hpp"

namespace net 
{
class Socket 
{
public:
      Socket(int domain, int type, int protocol);
      Socket(int domain, int type, Protocol protocol);
      ~Socket();

      /** Closes the socket descriptor */
      void Close() const;
      /** Sets the socket to blocking/non-blocking */
      void SetNonBlocking(const bool flag) const;
      /** Checks if the socket descriptor is valid */
      int IsValid() const;

      /** Gets the IP address of the remote host */
      std::string GetRemoteAddress() const;
      /** Gets the port of the remote host */
      uint16_t GetRemotePort() const;

      /* Getters */
      [[nodiscard]] int GetSocket() const;
private:
      int socket_;
};
}


#endif //SKYNET_SOCKET_HPP


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
