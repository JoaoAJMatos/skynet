//
// Created by JoaoAJMatos on 29/10/2023.
//

/** C++ includes */
#include <chrono>

/** Local Includes */
#include "time.hpp"

/**
* @brief Returns the current timestamp
* 
* @return std::time_t The current timestamp
*/
std::time_t util::time::timestamp() {
      return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());      
}

/**
* @brief Returns the current datetime as a string
* 
* @return std::string The datetime string
*/
std::string util::time::datetime() {
      return timestamp_to_datetime_string(timestamp(), DATETIME_FORMAT);
}

/**
* @brief Returns the current datetime as a string
* 
* @param std::time_t timestamp The timestamp to convert
* @param const char* format The format of the datetime string
* @return std::string The datetime string
*/
std::string util::time::timestamp_to_datetime_string(std::time_t timestamp, const char* format) {
      char buffer[80];
      std::strftime(buffer, 80, format, std::localtime(&timestamp));
      return std::string(buffer);
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
