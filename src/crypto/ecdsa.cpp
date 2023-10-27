//
// Created by João Matos on 26/09/2023.
//

/** Local includes */
#include "ecdsa.hpp"
#include "random.hpp"
#include "util.hpp"

/** C++ includes */
#include <cstring>
#include <iostream>

/** Skynet includes */
#include <macros.hpp>

/**
 * @brief Randomizes the given context with random data
 * 
 * @param context 
 */
void crypto::ecdsa::randomize_context(Context context) {
      int ret;
      byte randomizer[RANDOMIZER_BUFFER_SIZE];
      context = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
      
      /** Fill the randomizer buffer with random bytes */
      if (!crypto::random::fill_random(randomizer, RANDOMIZER_BUFFER_SIZE)) {
            throw crypto::ecdsa::Exception("Error generating randomness for the ECDSA context");
      }

      /** Randomize the context */
      ret = secp256k1_context_randomize(context, randomizer);
      ASSERT(ret, "Failed to randomize ECDSA context.");
}

/**
 * @brief Cleans up the given context
 * 
 * @param[i] context 
 */
inline void crypto::ecdsa::context_cleanup(Context context) {
      secp256k1_context_destroy(context);
}

/**
 * @brief Cleans up the given key pair.
 * 
 * @param key_pair 
 */
void crypto::ecdsa::key_pair_cleanup(KeyPair* key_pair) {
      crypto::util::secure_memzero(key_pair->private_key, sizeof(key_pair->private_key));
      crypto::util::secure_memzero(key_pair->public_key, sizeof(key_pair->public_key));
      delete key_pair;
}

/**
 * @brief Generates a new master key pair from the given seed for HD wallets
 * 
 * @param[i] context 
 * @param[i] seed 
 * @param[o] key_pair 
 */
void crypto::ecdsa::generate_master_key_pair(Context context, byte *seed, KeyPair* key_pair) {
      int ret;
      secp256k1_pubkey public_key;

      /** Key Generation */
      ret = secp256k1_ec_privkey_tweak_add(context, key_pair->private_key, seed);
      ASSERT(ret, "Failed to derive master private key from seed.");

      /** Public Key Creation */
      ret = secp256k1_ec_pubkey_create(context, &public_key, key_pair->private_key);
      ASSERT(ret, "Failed to derive public key from secret key.");

      /** Serialize Public Key */
      size_t output_len = COMPRESSED_PUBLIC_KEY_SIZE;
      if (!secp256k1_ec_pubkey_serialize(context, key_pair->public_key, &output_len, &public_key, SECP256K1_EC_COMPRESSED)) {
            throw crypto::ecdsa::Exception("Error serializing ECDSA public key");
      }
}

/**
 * @brief Generates a new ECDSA key pair
 * 
 * @param[i] Context  The ECDSA context
 * @param[o] KeyPair* The destination key pair 
 * @throws crypto::ecdsa::Exception
 */
void crypto::ecdsa::generate_key_pair(Context context, KeyPair* key_pair) {
      int ret;
      secp256k1_pubkey public_key;

      /* Key Generation */
      /** 
       * If the secret key is zero or out of range (bigger than secp256k1's
       * order), we try to sample a new key. Note that the probability of this
       * happening is negligible. 
       */
      loop() {
            if (!crypto::random::fill_random(key_pair->private_key, sizeof(key_pair->private_key))) {
                  throw crypto::ecdsa::Exception("Error generating randomness for the private key");
            }

            if (secp256k1_ec_seckey_verify(context, key_pair->private_key)) break;
      }

      /** Public Key Creation */
      ret = secp256k1_ec_pubkey_create(context, &public_key, key_pair->private_key);
      ASSERT(ret, "Failed to derive public key from secret key.");

      /** Serialize Public Key */
      size_t output_len = COMPRESSED_PUBLIC_KEY_SIZE;
      if (!secp256k1_ec_pubkey_serialize(context, key_pair->public_key, &output_len, &public_key, SECP256K1_EC_COMPRESSED)) {
            throw crypto::ecdsa::Exception("Error serializing ECDSA public key");
      }
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
