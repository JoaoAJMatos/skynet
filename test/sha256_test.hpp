/**
 * @file   ecdsa_test.hpp
 * @author JoaoAJMatos
 *
 * @brief SHA-256 interface unit tests
 *	    
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */


/* Skynet Includes */
#include <crypto/sha256.hpp>

/* Local Includes */
#include "unipp.hpp"


/**
 * This file tests the SHA-256 interface.
 *
 * We hash two different data and compare the hashes to ensure
 * that the interface is working properly.
 */
void HashTest() {
      byte data1[] = "Hello World!";
      byte data2[] = "Hello World Again!";
      byte hash1[crypto::SHA256_HASH_SIZE];
      byte hash2[crypto::SHA256_HASH_SIZE];
      
      crypto::SHA256::Hash(data1, sizeof(data1), hash1);
      crypto::SHA256::Hash(data2, sizeof(data2), hash2);

      ASSERT_FALSE(crypto::SHA256::CompareHash(hash1, hash2), "Hashes should be different!");
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
