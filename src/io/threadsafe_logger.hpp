/**
 * @file threadsafe_logger.hpp
 * @author JoaoAJMatos
 * @brief A thread-safe logger for the stdout and files
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_LOGGER_HPP
#define SKYNET_LOGGER_HPP

/** C++ includes */
#include <string>

namespace io::logging 
{
      enum class LogLevel : uint8_t {
            TRACE = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
      };

      class Logger
      {
      public:
            Logger() = default;
            Logger(const Logger&) = delete;
            void operator = (const Logger&) = delete;

            /** Get the singleton instance */
            static Logger* GetInstance();
            /** Log a message to the stdout and to a logfile */
            void Log(LogLevel level, const std::string& message, const std::string& filename = "");
      protected:
            static Logger* instance_;
            std::mutex lock_;
      };
}

#endif //SKYNET_LOGGER_HPP

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
