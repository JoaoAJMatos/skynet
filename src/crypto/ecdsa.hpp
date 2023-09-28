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

/* C++ includes */
#include <string>


namespace crypto
{
      /* CONSTANTS */
      constexpr int PRIVATE_KEY_SIZE = 32;
      constexpr int RANDOMIZER_BUFFER_SIZE = 32;      // Used for randomizing the context
      constexpr int COMPRESSED_PUBLIC_KEY_SIZE = 33;  // Compressed key for sharing
      constexpr int SERIALIZED_SIGNATURE_SIZE = 64;   // Serialized signature size
      constexpr int SIGNATURE_SIZE = 72;              // Signature size

      /** Return values for the ECDSA functions */
      enum ECError
      {
            OK = 0,                       // No error
            RANDOMNESS_ERROR = 1,         // Failed to generate randomness for creating the key pair
            CONTEXT_RANDOMIZE_ERROR = 2,  // Failed to randomize the context
            INVALID_PRIVATE_KEY = 3,      // Private key is invalid
            SERIALIZATION_ERROR = 4,      // Error serializing the public key
            PUBKEY_PARSE_ERROR = 5,       // Error parsing the public key
            SIGNATURE_ERROR = 6,          // Error signing hash with the given key 
            SIGNATURE_PARSE_ERROR = 7,    // Error parsing the signature
            SIGNATURE_INVALID = 8,        // Signature is invalid
            KEY_ERROR = 9                 // Error setting the key
      };

      class ECDSA
      {
      public:
            ECDSA();
            ~ECDSA();

            /* Generates a new ECDSA key pair */
            ECError MakeKeyPair();
            /* Sets the ECDSA secret and public keys given a secret key */
            ECError SetKey(byte *private_key);
            /* Signs a hash using the private key */
            ECError Sign(byte *hash, byte *signature);
            /* Verifies a signature using the public key */
            ECError Verify(byte *hash, byte *signature, byte *pubkey);

            /* Getters */
            byte *GetPrivateKey();
            ECError GetCompressedPublicKey(byte* pubkey);
      private:
            /* Member Variables */
            byte private_key_[PRIVATE_KEY_SIZE];
            secp256k1_pubkey public_key_;
            secp256k1_context *context_;
      };

      /** Converts an ECError to a string */
      std::string ECErrorToString(ECError error);
}

#endif // !#ifndef SKYNET_CRYPTO_ECDSA_HPP

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
