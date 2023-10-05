/**
 * @file stdout.hpp
 * @author JoaoAJMatos
 * @brief This file contains a series of utility functions to work with the stdout
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_STDOUT_HPP
#define SKYNET_STDOUT_HPP

#include <iostream>

/** Macros */
/** Basic colors for the stdout */
#ifdef _WIN32
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GRAY "\033[37m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#else
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define GRAY "\033[0;37m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#endif // _WIN32

/** Creates a colored string */
#define COLORED(color, message) std::string(color) + std::string(message) + std::string(RESET)

namespace io::stdout
{
      /** 
       * @brief Print a message to the stdout and add a new line
       *
       * @example 
       *    
       *    io::stdout::WriteLine(COLORED(GREEN, "Running unit tests..."));
       */
      inline void WriteLine(const std::string& message) {
            std::cout << message << std::endl;
      }
}

#endif // !SKYNET_STDOUT_HPP

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
