//
// Created by João Matos on 02/02/2023.
//

#ifndef SKYNET_COMMON_HPP
#define SKYNET_COMMON_HPP

#define SHA256_DIGEST_LENGTH 32
#define ECDSA_PRIVATE_KEY_LENGTH 32
#define ECDSA_COMPRESSED_PUBKEY_LENGTH 33

typedef enum {
    ERROR = -1,
    OK = 0,
} ErrorCode;

#endif //SKYNET_COMMON_HPP
