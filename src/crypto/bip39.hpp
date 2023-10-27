/**
 * @file bip39.hpp
 * @author JoaoAJMatos
 * @date 2023-10-16
 * 
 * @brief This file contains the BIP39 implementation for mnemonic generation and recovery
 *        of deterministic wallets.
 *
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_CRYPTO_BIP39_HPP
#define SKYNET_CRYPTO_BIP39_HPP

/** C++ Includes */
#include <iostream>
#include <vector>
#include <cstring>
#include <random>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <fstream>

/** Skynet Includes */
#include <crypto/sha256.hpp>
#include <types.hpp>

namespace crypto::bip39
{
      /**
       * @brief Generates random entropy for the mnemonic generation. (128 bits)
       *
       * @return std::vector<byte> The entropy generated.
       */
      static std::vector<byte> generate_entropy() {
            std::vector<byte> entropy(16);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 255);
            for (int i = 0; i < 16; i++) {
                  entropy[i] = dis(gen);
            }
            return entropy;
      }

      /**
       * @brief Validates the entropy provided.
       *
       * @param entropy The entropy to be validated.
       * @return true If the entropy is valid.
       */
      static bool validate_entropy(std::vector<byte> entropy) {
            return (entropy.size() % 4 != 0 || entropy.size() < 16 || entropy.size() > 32);
      }

      /**
       * @brief Calculates the checksum for the entropy provided.
       *
       * @param entropy The entropy to be used.
       * @return byte The checksum calculated.
       */
      static byte calculate_checksum(std::vector<byte> entropy) {
            std::vector<byte> hash;
            crypto::hashing::SHA256(entropy.data(), entropy.size(), hash.data());
            return hash[0] >> (8 - entropy.size() / 4);
      }

      /**
       * @brief Loads the word list from the file provided.
       * 
       * @param filename 
       * @return std::vector<std::string> 
       */
      static std::vector<std::string> load_word_list(std::string filename) {
            std::vector<std::string> word_list;
            std::ifstream file(filename);
            if (!file.is_open()) {
                  throw std::runtime_error("Could not open file.");
            }
            std::string line;
            while (std::getline(file, line)) {
                  word_list.push_back(line);
            }
            file.close();
            return word_list;
      }

      /**
       * @brief Splits the given mnemonic into words.
       * 
       * @param mnemonic 
       * @return std::vector<std::string> 
       */
      static std::vector<std::string> split_mnemonic_into_words(std::string mnemonic) {
            std::vector<std::string> words;
            std::stringstream ss(mnemonic);
            do {
                  std::string word;
                  ss >> word;
                  words.push_back(word);
            } while (ss);
            return words;
      }

      /**
       * @brief Generates a mnemonic from the entropy provided.
       *
       * @param entropy The entropy to be used.
       * @param word_list_file The file containing the word list.
       * @return std::string The mnemonic generated.
       */
      std::string generate_mnemonic(std::vector<byte> entropy, std::string word_list_file) {
            if (!validate_entropy(entropy)) {
                  throw std::runtime_error("Invalid entropy provided.");
            }
            
            std::vector<std::string> word_list = load_word_list(word_list_file);

            std::string mnemonic;
            for (int i = 0; i < entropy.size() * 8 / 32; i++) {
                  mnemonic += word_list[(entropy[i * 4] << 24 | 
                                         entropy[i * 4 + 1] << 16 | 
                                         entropy[i * 4 + 2] << 8 | 
                                         entropy[i * 4 + 3]) % 
                                         word_list.size()];

                  if (i != entropy.size() * 8 / 32 - 1) {
                        mnemonic += " ";
                  }
            }

            return mnemonic;
      }

      /**
       * @brief Decodes de mnemonic provided and outputs the seed.
       * 
       * @param[i] mnemonic 
       * @param[o] seed 
       */
      void decode_mnemonic(std::string mnemonic, std::string word_list_file, byte* seed) {
            std::vector<std::string> words = split_mnemonic_into_words(mnemonic);
            std::vector<std::string> word_list = load_word_list(word_list_file);
            std::vector<byte> data(words.size() * 4);

            for (const std::string& word : words) {
                  /** Find the word's index in the list */
                  int index = -1;
                  for (int i = 0; i < word_list.size(); i++) {
                        if (word_list[i] == word) {
                              index = i;
                              break;
                        }
                  }

                  if (index == -1) throw std::runtime_error("Word not found in the word list. Word: " + word);

                  /** Add the word's index as a 2 byte value to the data */
                  data.push_back(static_cast<byte>(index >> 8));
                  data.push_back(static_cast<byte>(index & 0xFF));
            }

            if (data.size() % 4 != 0 || data.size() < 16 || data.size() > 32) {
                  throw std::runtime_error("Invalid data length. Expected 16, 20, 24, 28 or 32 bytes; got " + std::to_string(data.size()));
            }

            /** Extract the checksum from the last byte and verify it */
            byte checksum = data.back() & 0xF;
            for (size_t i = 0; i < data.size() - 1; ++i) {
                  checksum ^= data[i];
            }

            if (checksum != 0) {
                  throw std::runtime_error("Invalid checksum.");
            }

            /** Remove the checksum from the data */
            data.pop_back();

            /** Copy the data to the seed and clear the data */
            memcpy(seed, data.data(), data.size());
            memset(data.data(), 0, data.size());
      }
} // namespace crypto::bip39

#endif // SKYNET_CRYPTO_BIP39_HPP

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
