/* Skynet includes */
#include <crypto/ecdsa.hpp>
#include <crypto/sha256.hpp>
#include <crypto/util.hpp>

/* Local includes */
#include "unipp.hpp"

void EcdsaTest() {
      byte data[] = "Hello World!";
      byte hash[crypto::SHA256_HASH_SIZE];
      byte signature[crypto::SIGNATURE_SIZE];
      byte public_key[crypto::COMPRESSED_PUBLIC_KEY_SIZE];
      crypto::ECError err;

      /** Create a new ECDSA object */
      crypto::ECDSA ecdsa = crypto::ECDSA();
      ecdsa.MakeKeyPair();

      /** Sign the hash */
      crypto::SHA256::Hash(data, sizeof(data), hash);
      err = ecdsa.Sign(hash, signature);
      show_bytes(signature, crypto::SIGNATURE_SIZE);
      
      /** Verify the signature */
      ecdsa.GetCompressedPublicKey(public_key);
      err = ecdsa.Verify(hash, signature, public_key);
      ASSERT_EQUAL(err, crypto::ECError::OK, "Failed to verify signature (" + crypto::ECErrorToString(err) + ")");
}
