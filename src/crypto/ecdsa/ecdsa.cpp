//
// Created by João Matos on 02/02/2023.
//

#include "ecdsa.hpp"
#include <util.hpp>

#if defined(_WIN32)
#include <windows.h>
#include <ntstatus.h>
#include <bcrypt.h>
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#include <sys/random.h>
#elif defined(__OpenBSD__)
#include <unistd.h>
#else
#error "Couldn't identify the OS"
#endif

#include <stdexcept>

/**
 * @brief Fills in a buffer with random data.
 *        This function follows best practices for obtaining
 *        randomness with different Operating Systems.
 *
 * @param data
 * @param size
 * @return ErrorCode - OK if successful, ERROR otherwise
 */
static ErrorCode fill_random(unsigned char* data, size_t size) {
#if defined(_WIN32)
    NTSTATUS res = BCryptGenRandom(NULL, data, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (res != STATUS_SUCCESS || size > ULONG_MAX) {
        return ERROR;
    } else {
        return OK;
    }
#elif defined(__linux__) || defined(__FreeBSD__)
    // If `getrandom(2)` is not available you should fallback to /dev/urandom
    ssize_t res = getrandom(data, size, 0);
    if (res < 0 || (size_t)res != size ) {
        return ERROR;
    } else {
        return OK;
    }
#elif defined(__APPLE__) || defined(__OpenBSD__)
    // If `getentropy(2)` is not available you should fallback to either /dev/urandom or `SecRandomCopyBytes`
    int res = getentropy(data, size);
    if (res == 0) {
        return OK;
    } else {
        return ERROR;
    }
#endif
    return ERROR;
}


/**
 * @brief Creates a new ECDSA Class instance.
 *        Initiates the context for the ECDSA algorithm and randomizes it
 *        to protect against side-channel leakage.
 */
crypto::CEcdsa::CEcdsa() {
    byte randomize[SHA256_DIGEST_LENGTH];
    this->ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);

    if (fill_random(randomize, sizeof(randomize)) != OK) {
        throw std::runtime_error("Could not generate randomness for ECDSA");
    }

    if (secp256k1_context_randomize(this->ctx, randomize) != 1) {
        throw std::runtime_error("Could not randomize ECDSA context");
    }
}

/**
 * @brief Destroys the ECDSA Class instance.
 *        Destroys the context for the ECDSA algorithm.
 */
crypto::CEcdsa::~CEcdsa() {
    secp256k1_context_destroy(this->ctx);
}

/**
 * @brief Generates a new ECDSA key pair.
 *        Generates a new private key and derives the public key from it.
 *
 * @param private_key
 * @param public_key
 * @return ErrorCode - OK if successful, ERROR otherwise
 */
ErrorCode crypto::CEcdsa::GenerateKeyPair(ecdsa_keypair_t *keypair) {
    secp256k1_pubkey pubkey;
    size_t pubkey_len;
    byte privkey[SHA256_DIGEST_LENGTH];

    // If the secret key is 0 or bigger than sec256k1's order, we need to regenerate it.
    // The probability of this happening is negligible, but we still account for it.
    while (true) {
        if (fill_random(privkey, sizeof(privkey)) != OK) return ERROR;
        if (secp256k1_ec_seckey_verify(this->ctx, privkey) == 1) break;
    }

    if (secp256k1_ec_pubkey_create(this->ctx, &pubkey, privkey) != 1) return ERROR;

    pubkey_len = sizeof(keypair->public_key);
    if (secp256k1_ec_pubkey_serialize(this->ctx, keypair->public_key, &pubkey_len, &pubkey, SECP256K1_EC_COMPRESSED) != 1) return ERROR;
    if (pubkey_len != sizeof(keypair->public_key)) return ERROR;
    memcpy(keypair->private_key, privkey, sizeof(keypair->private_key));
    return OK;
}

/**
 * @brief Signs a SHA256 hash with a private key.
 *
 * @param private_key
 * @param hash
 * @param signature
 * @return ErrorCode - OK if successful, ERROR otherwise
 */
ErrorCode crypto::CEcdsa::Sign(ecdsa_keypair_t *keypair, byte *hash, byte *signature_out) {
    secp256k1_ecdsa_signature sig;
    if (secp256k1_ecdsa_sign(this->ctx, &sig, hash, keypair->private_key, secp256k1_nonce_function_rfc6979, nullptr) != 1) return ERROR;
    if (secp256k1_ecdsa_signature_serialize_compact(this->ctx, signature_out, &sig) != 1) return ERROR;
    return OK;
}

/**
 * @brief Verifies a signature for a SHA256 hash with a public key.
 *
 * @param public_key
 * @param hash
 * @param signature
 * @return ErrorCode - OK if the signature is valid, ERROR otherwise
 */
ErrorCode crypto::CEcdsa::Verify(byte *public_key, byte *hash, byte *signature) {
    secp256k1_ecdsa_signature sig;
    secp256k1_pubkey pubkey;

    // Deserialize the public key & signature
    if (secp256k1_ec_pubkey_parse(this->ctx, &pubkey, public_key, sizeof(public_key)) != 1) return ERROR;
    if (secp256k1_ecdsa_signature_parse_compact(this->ctx, &sig, signature) != 1) return ERROR;

    if (secp256k1_ecdsa_verify(this->ctx, &sig, hash, &pubkey) != 1) return ERROR;
    return OK;
}

/**
 * @brief Derives a public key from a private key.
 *
 * @param private_key
 * @param public_key
 * @return ErrorCode - OK if successful, ERROR otherwise
 */
ErrorCode crypto::CEcdsa::PublicKeyFromPrivate(byte *private_key, byte *public_key) {
    secp256k1_pubkey pubkey;
    size_t pubkey_len;

    if (secp256k1_ec_pubkey_create(this->ctx, &pubkey, private_key) != 1) return ERROR;

    pubkey_len = sizeof(public_key);
    if (secp256k1_ec_pubkey_serialize(this->ctx, public_key, &pubkey_len, &pubkey, SECP256K1_EC_COMPRESSED) != 1) return ERROR;
    if (pubkey_len != sizeof(public_key)) return ERROR;
    return OK;
}

/**
 * @brief Shows the keypair in a human-readable format in the terminal.
 * @param keypair
 */
void crypto::CEcdsa::PrintKeyPair(ecdsa_keypair_t *keypair) {
    printf("Private key: ");
    print_hex(keypair->private_key, sizeof(keypair->private_key));
    printf("Public key: ");
    print_hex(keypair->public_key, sizeof(keypair->public_key));
}
