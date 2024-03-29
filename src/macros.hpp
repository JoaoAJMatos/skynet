/**
 * @file    macros.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the macros used throughout the project.
 *
 * @date    2023-09-28
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_MACROS_HPP
#define SKYNET_MACROS_HPP

/* C++ includes */
#include <cassert>

#ifdef __APPLE__
#define inline __attribute__((always_inline))
#endif // __APPLE__

#ifndef UNIPP
#define ASSERT(condition, message) assert((condition) && (message))
#endif

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define UNIMPLEMENTED() ASSERT(false, "Unimplemented")
#define loop() for (;;)

#define SHOW_BYTES(bytes, size) \
      for (int i = 0; i < size; i++) { \
            printf("%02x", bytes[i]); \
      } \
      printf("\n");

#endif // SKYNET_MACROS_HPP

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
