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
 * @brief Initializes the ECDSA object.
 */
crypto::ECDSA::ECDSA() {
      this->context_ = nullptr;
      std::memset(this->private_key_, 0, sizeof(this->private_key_));
      std::memset(&this->public_key_, 0, sizeof(this->public_key_));
}

/**
 * @brief Destroys the ECDSA object, frees the context and clears the
 *        private key.
 */
crypto::ECDSA::~ECDSA() {
      if (this->context_ != nullptr) {
            secp256k1_context_destroy(this->context_);
      }

      secure_memzero(this->private_key_, sizeof(this->private_key_));
}

/**
 * @brief Generates a new ECDSA key pair using Bitcoin's secp256k1
 *        library.
 */
crypto::ECError crypto::ECDSA::MakeKeyPair() {
      byte randomize[RANDOMIZER_BUFFER_SIZE];
      int return_value;

      /** Before we call the API functions we need to create the context */
      this->context_ = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
      if (!fill_random(randomize, sizeof(randomize))) {
            return crypto::ECError::RANDOMNESS_ERROR;
      }

      /** 
       * Randomizing the context is recommended to protect against side-channel
       * leakage according to the library documentation.
       *
       * See `secp256k1_context_randomize` in secp256k1.h for more information.
       *
       * This should never fail.
       */
      return_value = secp256k1_context_randomize(this->context_, randomize);
      ASSERT(return_value, "Failed to randomize ECDSA context.");

      /* Key Generation */
      /** 
       * If the secret key is zero or out of range (bigger than secp256k1's
       * order), we try to sample a new key. Note that the probability of this
       * happening is negligible. 
       */
      loop() {
            if (!fill_random(this->private_key_, sizeof(this->private_key_))) 
                  return crypto::ECError::RANDOMNESS_ERROR;

            if (secp256k1_ec_seckey_verify(this->context_, this->private_key_)) 
                  break;
      }

      /** Public key creation */
      return_value = secp256k1_ec_pubkey_create(this->context_, &this->public_key_, this->private_key_);
      ASSERT(return_value, "Failed to derive public key from secret key.");

      return crypto::ECError::OK;
}

/**
 * @brief Sets the secret and public keys according to the given key
 *
 * @param private_key The private key to set
 * @return crypto::ECError The error code
 */
crypto::ECError crypto::ECDSA::SetKey(byte *private_key) {
      int return_value;

      std::memcpy(this->private_key_, private_key, sizeof(this->private_key_));
      if (!secp256k1_ec_seckey_verify(this->context_, this->private_key_)) {
            return crypto::ECError::INVALID_PRIVATE_KEY;
      }

      return_value = secp256k1_ec_pubkey_create(this->context_, &this->public_key_, this->private_key_);
      ASSERT(return_value, "Failed to derive public key from secret key.");

      return crypto::ECError::OK;
}

/**
 * @brief Returns the public key in the compressed format (33 bytes)
 *
 * @param compressed_pubkey The buffer where the compressed public key will be stored
 * @return crypto::ECError The error code
 */
crypto::ECError crypto::ECDSA::GetCompressedPublicKey(byte* compressed_pubkey) {
      size_t output_len = COMPRESSED_PUBLIC_KEY_SIZE;

      /** Serialize the public key */
      if (!secp256k1_ec_pubkey_serialize(this->context_, compressed_pubkey, 
                                         &output_len, &this->public_key_, SECP256K1_EC_COMPRESSED))
            return crypto::ECError::SERIALIZATION_ERROR;

      return crypto::ECError::OK;
}

/**
 * @brief Signs the given hash using the ECDSA algorithm
 *
 * @param hash The hash to sign
 * @param signature The buffer where the signature will be stored
 * @return crypto::ECError The error code
 */
crypto::ECError crypto::ECDSA::Sign(byte *hash, byte *signature) {
      secp256k1_ecdsa_signature sig;

      /** Sign the hash */
      if (!secp256k1_ecdsa_sign(this->context_, &sig, hash, this->private_key_, nullptr, nullptr)) {
            return crypto::ECError::SIGNATURE_ERROR;
      }

      /** Serialize the signature */
      if (!secp256k1_ecdsa_signature_serialize_compact(this->context_, signature, &sig)) {
            return crypto::ECError::SERIALIZATION_ERROR;
      }

      return crypto::ECError::OK;
}

/**
 * @brief Verifies the given signature against the given hash and public key
 *
 * @param hash The hash to verify
 * @param signature The signature to verify
 * @param pubkey The public key to verify
 * @return ECError The error code
 */
crypto::ECError crypto::ECDSA::Verify(byte *hash, byte *signature, byte *pubkey) {
      secp256k1_pubkey public_key;
      secp256k1_ecdsa_signature sig;

      /** Parse the public key */
      if (!secp256k1_ec_pubkey_parse(this->context_, &public_key, pubkey, COMPRESSED_PUBLIC_KEY_SIZE)) {
            return crypto::ECError::PUBKEY_PARSE_ERROR;
      }

      /** Parse the signature */
      if (!secp256k1_ecdsa_signature_parse_compact(this->context_, &sig, signature)) {
            return crypto::ECError::SIGNATURE_PARSE_ERROR;
      }

      /** Verify the signature */
      if (!secp256k1_ecdsa_verify(this->context_, &sig, hash, &public_key)) {
            return crypto::ECError::SIGNATURE_ERROR;
      }

      return crypto::ECError::OK;
}

/**
 * @brief Returns the error string for the given error code
 *
 * @param error The error code
 * @return std::string The error string
 */
std::string crypto::ECErrorToString(crypto::ECError error) {
      switch (error) {
            case crypto::ECError::OK:
                  return "OK";
            case crypto::ECError::RANDOMNESS_ERROR:
                  return "Failed to generate random data";
            case crypto::ECError::CONTEXT_RANDOMIZE_ERROR:
                  return "Failed to randomize ECDSA context";
            case crypto::ECError::INVALID_PRIVATE_KEY:
                  return "Invalid private key";
            case crypto::ECError::SERIALIZATION_ERROR:
                  return "Failed to serialize data";
            case crypto::ECError::SIGNATURE_ERROR:
                  return "Failed to sign data";
            case crypto::ECError::SIGNATURE_INVALID:
                  return "Invalid signature";
            case crypto::ECError::PUBKEY_PARSE_ERROR:
                  return "Failed to parse public key";
            case crypto::ECError::SIGNATURE_PARSE_ERROR:
                  return "Failed to parse signature";
            case crypto::ECError::KEY_ERROR:
                  return "Failed to derive public key from secret key";
      } // No default case to force compiler warning if a new error is added
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
