#include <iostream>

#include <crypto/ecdsa/ecdsa.hpp>

int main() {
    crypto::CEcdsa ecdsa = crypto::CEcdsa();
    ecdsa_keypair_t keypair;

    ecdsa.GenerateKeyPair(&keypair);
    crypto::CEcdsa::PrintKeyPair(&keypair);

    return 0;
}
