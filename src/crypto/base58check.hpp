/**
 * @file   base58check.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains the Base58Check class definition.
 *        Skynet uses Base58Check to encode and decode addresses.
 *        Base58Check is a modified version of Base58 that adds a
 *        checksum to the encoded data to minimize the risks of errors
 *        when users transcribe or share addresses.
 *
 * @version 0.1
 * @date 2023-10-30
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_BASE58_CHECK_HPP
#define SKYNET_BASE58_CHECK_HPP

/* C++ includes */
#include <string>
#include <vector>

/* Skynet includes */
#include <types.hpp>

namespace crypto::encoding::base58check 
{
      /**
       * @brief Encodes a byte array to a Base58Check string
       * 
       * @param data The byte array to be encoded
       * @return std::string The Base58Check encoded string
       */
      std::string Encode(std::vector<byte> data);

      /**
       * @brief Decodes a Base58Check string to a byte array
       * 
       * @param data The Base58Check encoded string
       * @return std::vector<byte> The decoded byte array
       * @throws std::invalid_argument If the Base58Check string is invalid
       */
      std::vector<byte> Decode(std::string data);

      /**
       * @brief Encodes a Skynet address to a Base58Check string
       * 
       * @param address The address to be encoded
       * @param version The version of the address (check consensus.hpp for more info)
       * @return std::string The Base58Check encoded string
       */
      std::string EncodeAddress(std::vector<byte> address, int version);

      /**
       * @brief Decodes a Base58Check string to a Skynet address
       * 
       * @param[i] address The Base58Check encoded string
       * @param[o] version The version of the decoded address (check consensus.hpp for more info)
       * @return std::vector<byte> The decoded address
       * @throws std::invalid_argument If the Base58Check string is invalid
       */
      std::vector<byte> DecodeAddress(std::string address, int* version);

} // namespace crypto::encoding

#endif //SKYNET_BASE58_CHECK_HPP

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
