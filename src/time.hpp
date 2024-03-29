/**
 * @file   time.hpp
 * @author JoaoAJMatos
 *
 * @brief  This header file contains functions related to time. 
 *
 * @version 0.1
 * @date 2023-10-29
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_TIME_HPP
#define SKYNET_TIME_HPP

/* C++ includes */
#include <ctime>
#include <string>

namespace util::time
{
      constexpr const char* DATETIME_FORMAT = "%Y-%m-%d %H:%M:%S";

      /**
       * @brief Returns the current timestamp
       * 
       * @return std::time_t The current timestamp
       */
      std::time_t timestamp();

      /**
       * @brief Returns the current datetime as a string
       * 
       * @return std::string The datetime string
       */
      std::string datetime();

      /**
       * @brief Returns the current datetime as a string
       * 
       * @param std::time_t timestamp The timestamp to convert
       * @param const char* format The format of the datetime string
       * @return std::string The datetime string
       */
      std::string timestamp_to_datetime_string(std::time_t timestamp, const char* format);
}

#endif // SKYNET_TIME_HPP

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

