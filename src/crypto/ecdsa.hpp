/**
 * @file ecdsa.hpp
 * @author JoaoAJMatos
 * @brief libsecp256k1 wrapper
 * @date 2023-06-30
 * 
 * @details This class is a wrapper for the libsecp256k1 Bitcoin library.
 *          Simplifying the interface for ECDSA operations using the
 *          secp256k1 curve.
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_CRYPTO_ECDSA_HPP
#define SKYNET_CRYPTO_ECDSA_HPP

/* Bitcoin's secp256k1 library */
#include <secp256k1/secp256k1.h>

/* Skynet includes */
#include <types.hpp>
#include <crypto/bip39.hpp>

/* C++ includes */
#include <string>
#include <stdexcept>

namespace crypto::ecdsa
{
      /* CONSTANTS */
      constexpr int PRIVATE_KEY_SIZE = 32;
      constexpr int RANDOMIZER_BUFFER_SIZE = 32;      // Used for randomizing the context
      constexpr int COMPRESSED_PUBLIC_KEY_SIZE = 33;  // Compressed key for sharing
      constexpr int SERIALIZED_SIGNATURE_SIZE = 64;   // Serialized signature size
      constexpr int SIGNATURE_SIZE = 72;              // Signature size

      /** Type Aliases */
      using Context = secp256k1_context*;
      using Seed = byte[64];
      using Signature  = byte[SERIALIZED_SIGNATURE_SIZE];
      using PrivateKey = byte[PRIVATE_KEY_SIZE];
      using PublicKey  = byte[COMPRESSED_PUBLIC_KEY_SIZE];

      /**
       * @brief ECDSA Key Pair structure
       *
       * @details This structure holds the private and public keys
       *          for an ECDSA key pair.
       */
      struct KeyPair {
            PrivateKey private_key = {0};
            PublicKey  public_key  = {0};
      };

      /**
       * @brief ECDSA exception class
       */
      class Exception : public std::exception {
      public:
            Exception(const char* msg) : message(msg) {}
            const char* what() { return message; }
      private:
            const char* message;
      };

      /**
       * @brief Randomizes the given context
       * 
       * @param[i] context
       * @throws crypto::ecdsa::Exception
       */
      void randomize_context(Context context);

      /**
       * @brief Cleans up the given context
       * 
       * @param[i] context 
       */
      void context_cleanup(Context context);

      /** 
       * @brief Cleans up the KeyPair struct to clear secrets from memory 
       */
      void key_pair_cleanup(KeyPair* key_pair);

      /** 
       * @brief Generates a new master key pair for a hierarchical deterministic wallet 
       * 
       * @param[i] context The ECDSA context
       * @param[i] seed The seed to be used for the key pair generation
       * @param[o] key_pair The output key pair
       * @throws crypto::ecdsa::Exception
       */
      void generate_master_key_pair(Context context, byte *seed, KeyPair* key_pair);

      /**
       * @brief Generates a new ECDSA key pair
       * 
       * @param[i] context The ECDSA context
       * @throws crypto::ecdsa::Exception
       */
      void generate_key_pair(Context context, KeyPair* key_pair);

      /**
       * @brief Generates a new child key pair from the given master key pair
       * 
       * @param context 
       * @param master_key_pair 
       * @param child_key_pair 
       * @param index
       */
      void generate_child_key_pair_from_master(Context context, KeyPair* master_key_pair, KeyPair* child_key_pair, int index);

      /**
       * @brief Sign the given message using the provided key
       * 
       * @param context 
       * @param key_pair 
       * @param message 
       * @param signature 
       * @throws crypto::ecdsa::Exception
       */
      void sign(Context context, KeyPair* key_pair, byte* message, Signature signature);

      /**
       * @brief Verifies a signature using the given public key
       * 
       * @param context 
       * @param message 
       * @param signature 
       * @param public_key 
       * @return true 
       * @return false 
       */
      bool verify(Context context, byte* message, Signature signature, PublicKey public_key);

} // namespace crypto::ecdsa

#endif // #ifndef SKYNET_CRYPTO_ECDSA_HPP

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
