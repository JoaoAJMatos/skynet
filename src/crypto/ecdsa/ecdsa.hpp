/**
 * @file   ecdsa.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains the Wrapper for the secp256k1 library from Bitcoin core.
 *        This wrapper is used to provide a simpler interface for the library, since we don't
 *        need all of the functionality.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_ECDSA_HPP
#define SKYNET_ECDSA_HPP

#include <types.hpp>
#include <common.hpp>
#include <secp256k1/include/secp256k1.h>

#define ECDSA_SIGNATURE_LENGTH 64

typedef secp256k1_ecdsa_signature ecdsa_signature_t;

typedef struct {
    byte private_key[ECDSA_PRIVATE_KEY_LENGTH];
    byte public_key[ECDSA_COMPRESSED_PUBKEY_LENGTH];
} ecdsa_keypair_t;

namespace crypto {
    class CEcdsa {
    public:
        CEcdsa();
        ~CEcdsa();

        ErrorCode GenerateKeyPair(ecdsa_keypair_t *keypair);
        ErrorCode Sign(ecdsa_keypair_t *keypair, byte *hash, byte *signature_out);
        ErrorCode Verify(byte *public_key, byte *hash, byte *signature);
        ErrorCode PublicKeyFromPrivate(byte *private_key, byte *public_key);
        static void PrintKeyPair(ecdsa_keypair_t *keypair);
    private:
        secp256k1_context *ctx;
        secp256k1_pubkey pubkey;
        ecdsa_signature_t sig;
    };
}

#endif //SKYNET_ECDSA_HPP
