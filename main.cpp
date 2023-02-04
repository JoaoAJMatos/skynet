#include <iostream>

#include <crypto/ecdsa/ecdsa.hpp>
#include <crypto/sha256/sha256.hpp>
#include <util.hpp>

int main() {
    crypto::CEcdsa ecdsa = crypto::CEcdsa();
    crypto::CSHA256 sha256 = crypto::CSHA256();
    ecdsa_keypair_t keypair;
    byte data[] = "Hello World!";
    byte hash[32];
    byte signature[ECDSA_SIGNATURE_LENGTH];

    ecdsa.GenerateKeyPair(&keypair);
    crypto::CEcdsa::PrintKeyPair(&keypair);

    sha256.Hash(data, sizeof(data), hash);
    crypto::CSHA256::PrintHash(hash);

    ecdsa.Sign(&keypair, hash, signature);

    std::cout << "Signature: " << std::endl;
    print_hex(signature, ECDSA_SIGNATURE_LENGTH);

    ErrorCode res = ecdsa.Verify(keypair.public_key, hash, signature);
    if (res == ErrorCode::OK) {
        std::cout << "Signature is valid!" << std::endl;
    } else {
        std::cout << "Signature is invalid!" << std::endl;
    }
    return 0;
}
