//
// Creates by JoaoAJMatos on 29/10/2023.
//

/** C++ Includes */
#include <stdexcept>
#include <algorithm>

/** Skynet Includes */
#include <crypto/sha256.hpp>
#include <consensus.hpp>

/** Local Includes */
#include "base58check.hpp"


//////////////////////////////////////////////////////////////////////////////////////////////

static constexpr char BASE58_ALPHABET[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Hashes the given data twice using SHA256
 * 
 * @param data The data to be hashed
 * @return std::vector<byte> The double SHA256 hash
 */
static std::vector<byte> double_sha256(std::vector<byte> data) {
      std::vector<byte> hash;
      crypto::hashing::SHA256(data.data(), data.size(), hash.data());
      crypto::hashing::SHA256(hash.data(), hash.size(), hash.data());
      return hash;
}

/**
 * @brief Encodes a byte array to a Base58 string
 * 
 * @param data The byte array to be encoded
 * @return std::string The Base58 encoded string
 */
static std::string to_base58(std::vector<byte> data) {
      std::string base58 = "";
      int leading_zeros = 0;
      for (int i = 0; i < data.size() && data[i] == 0; i++) {
            leading_zeros++;
      }
      std::vector<byte> num(data.size() * 138 / 100 + 1);
      for (int i = data.size() - 1; i >= 0; i--) {
            int carry = data[i];
            for (int j = 0; j < num.size(); j++) {
                  carry += 256 * num[j];
                  num[j] = carry % 58;
                  carry /= 58;
            }
      }
      for (int i = 0; i < num.size() && num[i] == 0; i++) {
            base58 += BASE58_ALPHABET[0];
      }
      for (int i = num.size() - 1; i >= 0; i--) {
            base58 += BASE58_ALPHABET[num[i]];
      }
      return base58;
}

/**
 * @brief Decodes a Base58 string to a byte array
 * 
 * @param data The Base58 encoded string
 * @return std::vector<byte> The decoded byte array
 */
static std::vector<byte> from_base58(std::string data) {
      std::vector<byte> bytes;
      int leading_zeros = 0;
      for (int i = 0; i < data.size() && data[i] == BASE58_ALPHABET[0]; i++) {
            leading_zeros++;
      }
      std::vector<byte> num(data.size() * 733 / 1000 + 1);
      for (int i = data.size() - 1; i >= 0; i--) {
            int digit = std::find(BASE58_ALPHABET, BASE58_ALPHABET + 58, data[i]) - BASE58_ALPHABET;
            if (digit == -1) {
                  throw std::invalid_argument("Invalid Base58 string");
            }
            int carry = digit;
            for (int j = 0; j < num.size(); j++) {
                  carry += 58 * num[j];
                  num[j] = carry % 256;
                  carry /= 256;
            }
      }
      for (int i = 0; i < num.size() && num[i] == 0; i++) {
            bytes.push_back(0);
      }
      for (int i = num.size() - 1; i >= 0; i--) {
            bytes.push_back(num[i]);
      }
      return bytes;
}

//////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief Encodes a byte array to a Base58Check string
* 
* @param data The byte array to be encoded
* @return std::string The Base58Check encoded string
*/
std::string crypto::encoding::base58check::Encode(std::vector<byte> data) {
      std::vector<byte> checksum = double_sha256(data);
      checksum.resize(4);

      std::vector<byte> concatenated_data = data;
      concatenated_data.insert(concatenated_data.end(), checksum.begin(), checksum.end());

      return to_base58(concatenated_data);
}

/**
 * @brief Decodes a Base58Check string to a byte array
 * 
 * @param data The Base58Check encoded string
 * @return std::vector<byte> The decoded byte array
 * @throws std::invalid_argument If the Base58Check string is invalid
 */
std::vector<byte> crypto::encoding::base58check::Decode(std::string data) {
      std::vector<byte> decoded_data = from_base58(data);
      std::vector<byte> checksum = double_sha256(std::vector<byte>(decoded_data.begin(), decoded_data.end() - 4));
      checksum.resize(4);

      if (std::equal(decoded_data.end() - 4, decoded_data.end(), checksum.begin())) {
            return std::vector<byte>(decoded_data.begin(), decoded_data.end() - 4);
      } else {
            throw std::invalid_argument("Invalid Base58Check string");
      }
}

//////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief Encodes a Skynet address to a Base58Check string
* 
* @param address The address to be encoded
* @param version The version of the address (check consensus.hpp for more info)
* @return std::string The Base58Check encoded string
*/
std::string crypto::encoding::base58check::EncodeAddress(std::vector<byte> address, int version) {
      std::vector<byte> data;
      data.push_back(version);
      data.insert(data.end(), address.begin(), address.end());
      return Encode(data);
}

/**
* @brief Decodes a Base58Check string to a Skynet address
* 
* @param[i] address The Base58Check encoded string
* @param[o] version The version of the decoded address (check consensus.hpp for more info)
* @return std::vector<byte> The decoded address
* @throws std::invalid_argument If the Base58Check string is invalid
*/
std::vector<byte> crypto::encoding::base58check::DecodeAddress(std::string address, int* version) {
      std::vector<byte> decoded_address = Decode(address);
      *version = decoded_address[0];
      return std::vector<byte>(decoded_address.begin() + 1, decoded_address.end());
}

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