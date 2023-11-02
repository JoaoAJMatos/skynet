/**
 * @file stdin.hpp
 * @author JoaoAJMatos
 * @brief This file contains a series of utility functions to work with the stdin
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_STDIN_HPP
#define SKYNET_STDIN_HPP

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif // _WIN32 || _WIN64

namespace io::stdin
{
      /**
       * @brief Sets the stdin echo on or off
       *
       * @details Used for reading passwords
       *
       * @param enable If true, the echo will be enabled
       */
      void SetEcho(bool enable = true) {
#if defined(_WIN32) || defined(_WIN64)
            HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
            DWORD mode;
            GetConsoleMode(hStdin, &mode);

            if (!enable)
                  mode &= ~ENABLE_ECHO_INPUT;
            else
                  mode |= ENABLE_ECHO_INPUT;

            SetConsoleMode(hStdin, mode);
#else
            struct termios tty;
            tcgetattr(STDIN_FILENO, &tty);
            if (!enable)
                  tty.c_lflag &= ~ECHO;
            else
                  tty.c_lflag |= ECHO;

            (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
      }

      /**
       * @brief Reads a password from the stdin
       *
       * @details The echo is disabled while reading the password
       *
       * @param message The message to be displayed before reading the password
       * @return std::string The password
       */
      std::string ReadPassword(const std::string& message) {
            std::string password;

            SetEcho(false);
            std::cout << message;
            std::cin >> password;
            SetEcho(true);

            return password;
      }
}

#endif // !SKYNET_STDIN_HPP

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
