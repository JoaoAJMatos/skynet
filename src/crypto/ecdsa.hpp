/**
 * @file ecdsa.hpp
 * @author JoaoAJMatos
 * @brief libsecp256k1 wrapper
 * @date 2023-06-30
 * 
 * @details This class is a wrapper for the libsecp256k1 library.
 *          Simplifying the interface for ECDSA operations using the
 *          secp256k1 curve.
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_CRYPTO_ECDSA_HPP
#define SKYNET_CRYPTO_ECDSA_HPP

#include <secp256k1.h>
#include <types.hpp>

namespace crypto
{
      class ECDSA
      {
      public:
            ECDSA();
            ~ECDSA();

            void GenerateKeyPair();
            void Sign(byte *hash, byte *signature);
            bool Verify(byte *hash, byte *signature, byte *public_key);

            byte *GetPrivateKey();
            byte *GetPublicKey();
      private:
            byte private_key_[32];
            secp256k1_pubkey public_key_;
            secp256k1_context *context_;
      };
}

#endif // !#ifndef SKYNET_CRYPTO_ECDSA_HPP
