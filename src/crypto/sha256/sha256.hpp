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
 *    byte hash[SHA256_HASH_LENGTH];
 *    byte data[] = "Hello World!";
 *
 *    crypto::CSha256::Update(data, sizeof(data));
 *    crypto::CSha256::Final(hash);
 *    crypto::CSha256::PrintHash(hash);
 *
 * return 0;
 * }
 */

#ifndef SKYNET_SHA256_HPP
#define SKYNET_SHA256_HPP

#include <types.hpp>
#include <string>
#include <array>

namespace crypto {
    class CSHA256 {
    public:
        CSHA256();
        ~CSHA256();

        void Update(const byte *data, size_t len);
        void Final(byte *hash);

        void Hash(const byte *data, size_t len, byte *hash);
        void HashFile(const std::string &filename, byte *hash);

        static void PrintHash(byte *hash);
    private:
        byte data[64];
        word data_size;
        unsigned long long bit_len;
        word state[8];
    };
}

#endif //SKYNET_SHA256_HPP
