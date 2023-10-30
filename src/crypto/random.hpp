/**
 * @file   random.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains randomness generation utility functions used
 *        for initializing the context of the ECDSA class.
 *
 *        It's a collection of the best practice methods for generating randomness
 *        with different operating systems.
 *
 * @details Platform randomness sources:
 *
 *        Linux   -> `getrandom(2)`(`sys/random.h`), if not available `/dev/urandom` should be used. 
 *                http://man7.org/linux/man-pages/man2/getrandom.2.html, 
 *                https://linux.die.net/man/4/urandom
 *
 *        macOS   -> `getentropy(2)`(`sys/random.h`), if not available `/dev/urandom` should be used. 
 *                https://www.unix.com/man-page/mojave/2/getentropy, 
 *                https://opensource.apple.com/source/xnu/xnu-517.12.7/bsd/man/man4/random.4.auto.html
 *
 *        FreeBSD -> `getrandom(2)`(`sys/random.h`), if not available `kern.arandom` should be used. 
 *                https://www.freebsd.org/cgi/man.cgi?query=getrandom, 
 *                https://www.freebsd.org/cgi/man.cgi?query=random&sektion=4
 *
 *        OpenBSD -> `getentropy(2)`(`unistd.h`), if not available `/dev/urandom` should be used. 
 *                https://man.openbsd.org/getentropy, https://man.openbsd.org/urandom
 *
 *        Windows -> `BCryptGenRandom`(`bcrypt.h`). 
 *                https://docs.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgenrandom
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_RANDOM_HPP
#define SKYNET_RANDOM_HPP

#if defined(_WIN32)
/**
 * The defined WIN32_NO_STATUS macro disables return code definitions in
 * windows.h, which avoids "macro redefinition" MSVC warnings in ntstatus.h.
 */
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS
#include <ntstatus.h>
#include <bcrypt.h>
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#include <sys/random.h>
#elif defined(__OpenBSD__)
#include <unistd.h>
#else
#error "Unable to identify the operating system."
#endif // defined(_WIN32)

/* C++ includes */
#include <stddef.h>
#include <limits.h>
#include <stdio.h>

namespace crypto::random
{
      /**
       * @brief   Fills the given buffer with random bytes.
       *
       * @details In case the prefered function for getting randomness
       *          is not available or fails on POSIX systems, we should
       *          fallback to `/dev/urandom` to extract the randomness
       *          we need.
       * 
       * @param data The buffer to be filled with random bytes.
       * @param size The size of the buffer.
       * @return int 1 if the operation was successful, 0 otherwise.
       */
      static int urandom_bytes(byte* data, size_t size) {
            FILE* urandom = fopen("/dev/urandom", "rb");
            if (urandom == NULL) {
                  return 0;
            }
            size_t read = fread(data, 1, size, urandom);
            fclose(urandom);
            return read == size;
      }

      /**
       * @brief Fills the given buffer with random bytes.
       * 
       * @param data The buffer to be filled with random bytes.
       * @param size The size of the buffer.
       * @return int 1 if the operation was successful, 0 otherwise.
       */
      int fill_random(byte* data, size_t size) {
#if defined(_WIN32)
            if (BCryptGenRandom(NULL, data, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != STATUS_SUCCESS) {
                  return 0;
            }
#elif defined(__linux__) || defined(__FreeBSD__)
            /* If `getrandom(2)` is not available, you should fallback to /dev/urandom */
            if (getrandom(data, size, 0) != size) {
                  return 0;
            }

            /* Fallback to /dev/urandom */
            urandom_bytes(data, size);
#elif defined(__APPLE__) || defined(__OpenBSD__)
            if (getentropy(data, size) != 0) {
                  return 0;
            }

            /* Fallback to /dev/urandom */
            urandom_bytes(data, size);
#endif
            return 1;
      }

      /**
       * @brief Generates a random integer between two values
       * 
       * @param min 
       * @param max 
       * @return int 
       */
      inline int randint(int min, int max) {
            srand(time(NULL));
            return min + (int) (rand() / (RAND_MAX / (max - min + 1) + 1));
      }
} // namespace random

#endif // SKYNET_RANDOM_HPP

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
