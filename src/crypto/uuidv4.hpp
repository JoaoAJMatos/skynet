/**
 * @file uuidv4.hpp
 * @author JoaoAJMatos
 * @date 2023-06-30
 * 
 * @brief This file contains UUIDv4 generation utilities following the
 *        RFC-4122 specification.
 *
 * @copyright Copyright (c) 2023
 */

#ifndef CRYPTO_UUIDV4_HPP
#define CRYPTO_UUIDV4_HPP

/** C++ includes */
#include <random>
#include <string>

/** Skynet includes */
#include <types.hpp>

namespace crypto
{
      static constexpr char HEX[] = "0123456789abcdef";

      static std::string uuidv4() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 15);
            std::uniform_int_distribution<> dis2(8, 11);
            std::uniform_int_distribution<> dis3(0, 3);
            std::uniform_int_distribution<> dis4(0, 255);

            std::string uuid = "";
            for (int i = 0; i < 8; i++) {
                  uuid += HEX[dis(gen)];
            }
            uuid += "-";
            for (int i = 0; i < 4; i++) {
                  uuid += HEX[dis(gen)];
            }
            uuid += "-4";
            for (int i = 0; i < 3; i++) {
                  uuid += HEX[dis(gen)];
            }
            uuid += "-";
            uuid += HEX[dis2(gen)];
            for (int i = 0; i < 3; i++) {
                  uuid += HEX[dis(gen)];
            }
            uuid += "-";
            for (int i = 0; i < 12; i++) {
                  uuid += HEX[dis(gen)];
            }
            return uuid; 
      }
} // namespace crypto

#endif // CRYPTO_UUIDV4_HPP
