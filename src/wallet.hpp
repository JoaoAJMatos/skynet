/**
 * @file    wallet.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the Wallet class definition.
 *          A Wallet is a data structure that represents a single Wallet
 *          in the Network. Wallets represent accounts in Skynet. A single
 *          Wallet can have multiple addresses.
 *
 * @date    2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_WALLET_HPP
#define SKYNET_WALLET_HPP

/** C++ Includes */
#include <vector>

/** Skynet Includes */
#include <types.hpp>
#include <crypto/ecdsa.hpp>

namespace skynet
{
      struct WalletAddress
      {
            byte address[crypto::COMPRESSED_PUBLIC_KEY_SIZE];
            byte private_key[crypto::PRIVATE_KEY_SIZE];
      };

      class Wallet
      {
      public:
            Wallet();
            ~Wallet();

            /* WALLET FILES */
            /** Load a Wallet from an encrypted wallet file */
            void LoadFromFile(std::string file_path, std::string password);
            /** Saves the Wallet to a file */
            void SaveToFile(std::string file_path, std::string password);

            /* SIGNING AND VERIFYING */
            /** Signs a message with the Wallet's private key */
            bool Sign(byte *message, byte *signature);
            /** Verifies a signature with a private key */
            bool Verify(byte *message, byte *signature, byte *public_key);

            /* ADDRESSES */
            /** Generates a new address for the Wallet */
            void GenerateAddress();

            /* COINS */
            /** Returns the total balance of the Wallet */
            uint64_t GetBalance();
            /** Returns the balance of a given address in the Wallet */
            uint64_t GetBalance(byte *address);

      private:
            std::vector<WalletAddress> addresses;

      protected:
            /** The ECDSA object used to sign and verify data */
            crypto::ECDSA ecdsa;
      };
}

#endif // !SKYNET_WALLET_HPP
