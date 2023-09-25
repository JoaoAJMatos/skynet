//
// Created by João Matos on 02/02/2023.
//

/* C++ includes */
#include <fstream>

/* Skynet includes */
#include "sha256.hpp"

/* Rotates a word to the left/right by n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))

/* Ch, Maj, Sigma and Epsilon functions */
#define CHOOSE(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJORITY(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EPSILON_0(x) (ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22))
#define EPSILON_1(x) (ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25))
#define SIGMA_0(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ ((x) >> 3))
#define SIGMA_1(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ ((x) >> 10))

/* Constants */
/* The first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311 */
constexpr std::array<word, 64> K = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};


static void sha256_transform(word *state, const byte* data) {
    word a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

    for (i = 0, j = 0; i < 16; ++i, j += 4) {
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    }

    for (; i < 64; ++i) {
        m[i] = SIGMA_1(m[i - 2]) + m[i - 7] + SIGMA_0(m[i - 15]) + m[i - 16];
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (i = 0; i < 64; ++i) {
        t1 = h + EPSILON_1(e) + CHOOSE(e, f, g) + K[i] + m[i];
        t2 = EPSILON_0(a) + MAJORITY(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

/**
 * @brief Constructs a new SHA256 object and initializes the state.
 */
crypto::SHA256::SHA256() {
    this->data_size = 0;
    this->bit_len = 0;
    this->state[0] = 0x6a09e667;
    this->state[1] = 0xbb67ae85;
    this->state[2] = 0x3c6ef372;
    this->state[3] = 0xa54ff53a;
    this->state[4] = 0x510e527f;
    this->state[5] = 0x9b05688c;
    this->state[6] = 0x1f83d9ab;
    this->state[7] = 0x5be0cd19;
}

crypto::SHA256::~SHA256() {
    memset(this->data, 0, 64);
    memset(this->state, 0, 8);
    this->data_size = 0;
    this->bit_len = 0;
}


/**
 * @brief Updates the hash with the given data.
 * @param data The data to be hashed.
 * @param len The length of the data.
 */
void crypto::SHA256::Update(const byte* input_data, size_t len) {
      word i;
      for (i = 0; i < len; ++i) {
            this->data[this->data_size] = input_data[i];
            this->data_size++;
            if (this->data_size == 64) {
                  sha256_transform(this->state, this->data);
                  this->bit_len += 512;
                  this->data_size = 0;
            }
      }
}

/**
 * @brief Finalizes the hash and sets the digest.
 */
void crypto::SHA256::Final(byte *hash) {
      word i = this->data_size;

      if (this->data_size < 56) {
            this->data[i++] = 0x80;
            while (i < 56) {
                  this->data[i++] = 0x00;
            }
      } else {
            this->data[i++] = 0x80;
            while (i < 64) {
                  this->data[i++] = 0x00;
            }
            sha256_transform(this->state, this->data);
            memset(this->data, 0, 56);
      }

      this->bit_len += this->data_size * 8;
      this->data[63] = this->bit_len;
      this->data[62] = this->bit_len >> 8;
      this->data[61] = this->bit_len >> 16;
      this->data[60] = this->bit_len >> 24;
      this->data[59] = this->bit_len >> 32;
      this->data[58] = this->bit_len >> 40;
      this->data[57] = this->bit_len >> 48;
      this->data[56] = this->bit_len >> 56;
      sha256_transform(this->state, this->data);

      // Reverse the byte order since we are using little endian (SHA256 uses big endian).
      for (i = 0; i < 4; ++i) {
            hash[i] = (this->state[0] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 4] = (this->state[1] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 8] = (this->state[2] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 12] = (this->state[3] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 16] = (this->state[4] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 20] = (this->state[5] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 24] = (this->state[6] >> (24 - i * 8)) & 0x000000ff;
            hash[i + 28] = (this->state[7] >> (24 - i * 8)) & 0x000000ff;
      }
}

/**
 * @brief Calculates the SHA256 hash of the given data.
 * @param input_data
 * @param len
 * @param hash
 */
void crypto::SHA256::Hash(const byte *input_data, size_t len, byte *hash) {
      crypto::SHA256 sha256;
      sha256.Update(input_data, len);
      sha256.Final(hash);
      memset(&sha256, 0, sizeof(crypto::SHA256));
}

/**
 * @brief Calculates the hash of a file with a given name.
 * @param filename
 * @param hash
 */
static void crypto::SHA256::HashFile(const std::string &filename, byte *hash) {
      crypto::SHA256 sha256;
      byte buffer[1024];
      std::ifstream file(filename, std::ios::binary);

      if (!file.is_open()) {
            throw std::runtime_error("Could not open file.");
      }

      while (!file.eof()) {
            file.read((char*)buffer, 1024);
            sha256.Update(buffer, file.gcount());
      }

      sha256.Final(hash);
      file.close();
      memset(&sha256, 0, sizeof(crypto::SHA256));
}


/**
 * @brief Compares two hashes.
 * @param hash1
 * @param hash2
 * @return True if the hashes are equal, false otherwise.
 */
bool crypto::SHA256::CompareHash(const byte *hash1, const byte *hash2) {
      for (int i = 0; i < SHA256_HASH_LENGTH; i++) {
            if (hash1[i] != hash2[i]) {
                  return false;
            }
      }
      return true;
}


/**
 * @brief Prints a hash to the stdout.
 * @param hash
 */
void crypto::SHA256::PrintHash(byte *hash) {
      for (int i = 0; i < SHA256_HASH_LENGTH; i++) {
            printf("%02x", hash[i]);
      }
      printf("\n");
}

