/**
 * @file   ipc.hpp
 * @author JoaoAJMatos
 *
 * @brief  This header file contains the logic fot the
 *         inter-process communication (IPC) system.
 *
 * @version 0.1
 * @date 2023-11-10
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_IPC_HPP
#define SKYNET_IPC_HPP

/* C++ includes */
#include <string>
#include <stdexcept>

/* Local includes */
#include "types.hpp"


namespace skynet
{
      class IPCException : public std::runtime_error
      {
      public:
            IPCException(const std::string& message) : std::runtime_error(message) {}
      };

      /**
       * This class implements the inter-process communication (IPC) system.
       * Skynet uses this system to orchestrate the communications between the 
       * node and the miner (check core/node/node.hpp), as well as other processes.
       */
      class IPC
      {
      public:
            IPC(const std::string& pipe_name) : pipe_name(pipe_name) {}
            ~IPC() {}

            /**
             * @brief Writes a message to the pipe.
             *
             * @param message The message to be written.
             */
            void WriteToPipe(const std::string& message);

            /**
             * @brief Reads a message from the pipe.
             *
             * @return std::string The message read from the pipe.
             */
            void WriteToPipe(std::vector<byte> data);

            /**
             * @brief Reads a message from the pipe.
             *
             * @return std::string The message read from the pipe.
             */
            std::string ReadFromPipe();

            /**
             * @brief Reads a message from the pipe.
             *
             * @return std::string The message read from the pipe.
             */
            std::vector<byte> ReadFromPipeAsBytes();
            
      private:
            std::string pipe_name;
      };

} // namespace skynet

#endif // SKYNET_IPC_HPP

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

