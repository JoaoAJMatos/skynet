/**
 * @file util.hpp
 * @author JoaoAJMatos
 * @date 2023-06-30
 * 
 * @brief This file contains some utility functions for the cryptography interface
 *        like memory management functions for clearing secrets from memory, and
 *        functions to display bytes formatted on the stdout.
 *
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_CRYPTO_MEMORY_HPP
#define SKYNET_CRYPTO_MEMORY_HPP

#include <cstring>    // For memset

#if defined(_MSC_VER)
#include <windows.h>  // For SecureZeroMemory
#endif

namespace crypto::util
{
      /**
       * @brief Clears the memory pointed by ptr with the given length
       *        to prevent leaking secrets.
       * 
       * @param ptr Pointer to the memory to be cleared
       * @param len Length of the memory to be cleared
       */
      static void secure_memzero(void *ptr, size_t len) {
#if defined(_MSC_VER)
            SecureZeroMemory(ptr, len);
#elif defined(__GNUC__)
            /* We use a memory barrier that scares the compiler away from optimizing out the memset.
             *
             * Quoting Adam Langley <agl@google.com> in commit ad1907fe73334d6c696c8539646c21b11178f20f
             * in BoringSSL (ISC License):
             *    As best as we can tell, this is sufficient to break any optimisations that
             *    might try to eliminate "superfluous" memsets.
             *
             * This method used in memzero_explicit() the Linux kernel, too. Its advantage is that it is
             * pretty efficient, because the compiler can still implement the memset() efficiently,
             * just not remove it entirely. See "Dead Store Elimination (Still) Considered Harmful" by
             * Yang et al. (USENIX Security 2017) for more background.
             */
            memset(ptr, 0, len);
            __asm__ __volatile__("" : : "r"(ptr) : "memory");
#else
            void *(*volatile const volatile_memset)(void *, int, size_t) = memset;
            volatile_memset(ptr, 0, len);
#endif
      }
} // namespace crypto::util

#endif // !SKYNET_CRYPTO_MEMORY_HPP

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
