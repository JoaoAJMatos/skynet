/**
 * @file   sha256.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains the SHA256 hashing algorithm implementation and wrapper.
 *        This implementation was inspired by B-Con's SHA256 implementation in C. You can find
 *        the original implementation here: https://github.com/B-Con/crypto-algorithms/blob/master/sha256.h
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 *
 *
 * @example
 * #include <sha256.hpp>
 *
 * int main() {
 *      byte data[] = "Hello World!";
 *      byte hash[SHA256_HASH_LENGTH];
 *     
 *      crypto::SHA256::Hash(data, sizeof(data), hash);
 *      return 0;
 * }
 */

#ifndef SKYNET_SHA256_HPP
#define SKYNET_SHA256_HPP

/* C++ includes */
#include <string>
#include <array>
#include <cstring>

/* Skynet includes */
#include <types.hpp>

#define SHA256_HASH_LENGTH 32
#define SHA256_BLOCK_SIZE 64

namespace crypto 
{
class SHA256 
{
public:
      SHA256();
      ~SHA256();
      
      /* Hashes the given data and outputs the digest to byte *hash */
      static void Hash(const byte *data, size_t len, byte *hash);
      /* Hashes the given file and outputs the digest to byte *hash */
      static void HashFile(const std::string &filename, byte *hash);
      /* Compares two hashes, true if equal, false if not */
      static bool CompareHash(const byte *hash1, const byte *hash2);
      /* Prints a hash to the stdout */
      static void PrintHash(byte *hash);
private:
      /* Private Functions */
      void Update(const byte *data, size_t len);
      void Final(byte *hash);

      /* Member Variables */
      byte data[SHA256_BLOCK_SIZE];
      word data_size;
      unsigned long long bit_len;
      word state[8];
};
}

#endif //SKYNET_SHA256_HPP

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
