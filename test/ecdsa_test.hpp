#include <crypto/ecdsa.hpp>

#include "unipp.hpp"

void EcdsaSign() {
}

void EcdsaVerify() {
}

void EcdsaTest() {
      crypto::ECDSA ecdsa;
      byte hash[32];
      byte signature[64];
      byte public_key[33];

      ecdsa.GenerateKeyPair();
      ecdsa.Sign(hash, signature);
      ecdsa.GetPublicKey(public_key);

      ASSERT_TRUE(ecdsa.Verify(hash, signature, public_key), "Signature should be valid!");
}
