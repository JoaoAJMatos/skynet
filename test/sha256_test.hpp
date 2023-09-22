#include <crypto/sha256.hpp>

#include "unipp.hpp"

void HashTest() {
      byte data1[] = "Hello World!";
      byte data2[] = "Hello World Again!";
      byte hash1[SHA256_HASH_LENGTH];
      byte hash2[SHA256_HASH_LENGTH];
      
      crypto::SHA256::Hash(data1, sizeof(data1), hash1);
      crypto::SHA256::Hash(data2, sizeof(data2), hash2);

      ASSERT_FALSE(crypto::SHA256::CompareHash(hash1, hash2), "Hashes should be different!");
}
