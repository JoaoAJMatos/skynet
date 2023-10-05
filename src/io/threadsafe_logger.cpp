//
// Created by João Matos on 01/02/2023.
//

/** C++ includes */
#include <iostream>
#include <mutex>
#include <vector>

/** Skynet includes */
#include <time.hpp>
#include <io/file.hpp>
#include <io/stdout.hpp>

/** Local includes */
#include "threadsafe_logger.hpp"

/** HELPER FUNCTIONS */
static inline void TRACE(const std::string& message) { io::stdout::WriteLine(COLORED(GRAY, message)); }
static inline void DEBUG(const std::string& message) { io::stdout::WriteLine(COLORED(GREEN, message)); }
static inline void INFO(const std::string& message)  { io::stdout::WriteLine(COLORED(BLUE, message)); }
static inline void WARN(const std::string& message)  { io::stdout::WriteLine(COLORED(YELLOW, message)); }
static inline void ERROR(const std::string& message) { io::stdout::WriteLine(COLORED(RED, message)); }

/** Singleton instance */
io::logging::Logger* io::logging::Logger::instance_ = nullptr;

/**
 * @brief Get the singleton instance
 *
 * @return Logger*
 */
io::logging::Logger* io::logging::Logger::GetInstance() {
      if (instance_ == nullptr) {
            instance_ = new Logger();
      }
      
      return instance_;
}

/**
 * @brief Log a message to the stdout
 *
 * @param level
 * @param message
 */
void io::logging::Logger::Log(io::logging::LogLevel level, const std::string& message, const std::string& filename) {
      std::lock_guard<std::mutex> lock(lock_);
      std::string log_message = "[" + util::time::datetime() + "] " + message;
      
      switch (level) {
            case LogLevel::TRACE:
                  TRACE(log_message);
                  break;
            case LogLevel::DEBUG:
                  DEBUG(log_message);
                  break;
            case LogLevel::INFO:
                  INFO(log_message);
                  break;
            case LogLevel::WARN:
                  WARN(log_message);
                  break;
            case LogLevel::ERROR:
                  ERROR(log_message);
                  break;
      }

      if (filename != "") {
            io::file::Append(filename, log_message);
      }
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
