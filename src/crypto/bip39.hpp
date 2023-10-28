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
#include <vector>
#include <string>

/** Skynet Includes */
#include <types.hpp>

namespace crypto::bip39
{
      /**
       * @brief Generates a mnemonic from the entropy provided.
       *
       * @param entropy The entropy to be used.
       * @param word_list_file The file containing the word list.
       * @return std::string The mnemonic generated.
       */
      std::string generate_mnemonic(std::vector<byte> entropy, std::string word_list_file);

      /**
       * @brief Decodes de mnemonic provided and outputs the seed.
       * 
       * @param[i] mnemonic 
       * @param[o] seed 
       */
      void decode_mnemonic(std::string mnemonic, std::string word_list_file, byte* seed);
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
