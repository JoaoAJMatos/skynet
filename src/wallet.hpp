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

            /* RECOVERING */
            /** Recovers a Wallet from a mnemonic and a password */
            void Recover(std::string mnemonic, std::string password);

            /* ADDRESSES */
            /** Generates a new address for the Wallet */
            void GenerateAddress();

            /* COINS */
            /** Returns the total balance of the Wallet */
            uint64_t GetBalance();
            /** Returns the balance of a given address in the Wallet */
            uint64_t GetBalance(byte *address);

      private:
            /** Parent key */
            /**
             * @brief The master key is the key that is used to generate
             *        all the child keys using the BIP32 algorithm.
             */
            crypto::ecdsa::KeyPair master;

            /** Child keys */
            std::vector<crypto::ecdsa::KeyPair> addresses;
      };
}

#endif // SKYNET_WALLET_HPP
