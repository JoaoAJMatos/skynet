/* Test Imports */
#include "sha256_test.hpp"
#include "ecdsa_test.hpp"

/* UNIPP test framework */
#include "unipp.hpp"

int main(void) {
      RUN(
            SUITE("Hashing Interface", "Tests Skynet's cryptography interface",
                  TEST("Sha-256 Test", "Tests the SHA256 hash function", HashTest)
            )
      );

      return 0;
}
