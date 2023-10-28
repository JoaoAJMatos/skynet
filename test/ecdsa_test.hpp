/**
 * @file   ecdsa_test.hpp
 * @author JoaoAJMatos
 *
 * @brief ECDSA interface unit tests
 *	    
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */


/* Skynet includes */
#include <crypto/ecdsa.hpp>
#include <crypto/sha256.hpp>
#include <crypto/util.hpp>
#include <macros.hpp>

/* Local includes */
#include "unipp.hpp"


/**
 * This file tests the ECDSA interface.
 *
 * We hash the data, sign the hash and verify the signature, all
 * while simulating the serialization and deserialization process
 * of the signature and public key to ensure that the interface
 * is working properly.
 */
void EcdsaTest() {
      byte data[] = "Hello World!";
      byte hash[crypto::hashing::SHA256_HASH_SIZE];
      byte signature[crypto::ecdsa::SERIALIZED_SIGNATURE_SIZE];
      byte public_key[crypto::ecdsa::COMPRESSED_PUBLIC_KEY_SIZE];

      /** Create and randomize the context */
      crypto::ecdsa::Context context;
      crypto::ecdsa::randomize_context(context);

      /** Use the context to create the Key Pair */
      crypto::ecdsa::KeyPair key_pair;
      crypto::ecdsa::generate_key_pair(context, &key_pair);

      /** Sign the hash */
      crypto::hashing::SHA256(data, sizeof(data), hash);
      crypto::ecdsa::sign(context, &key_pair, hash, signature);
      
      /** Verify the signature */
      bool isValid = crypto::ecdsa::verify(context, signature, hash, key_pair.public_key);
      ASSERT_TRUE(isValid, "Failed to verify signature");
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
