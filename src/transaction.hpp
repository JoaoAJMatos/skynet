/**
 * @file    transaction.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the Transaction class definition.
 *          A Transaction is a data structure that represents a single Transaction
 *          in the Network.
 *
 * @date    2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_TRANSACTION_HPP
#define SKYNET_TRANSACTION_HPP

/** Skynet includes */
#include <types.hpp>
#include <crypto/ecdsa.hpp>
#include <crypto/sha256.hpp>

namespace skynet
{
      /**
       * @brief The transaction OutputMap struct stores all
       *        the information about a transaction regarding
       *        the sender and the recipient.
       */
      struct OutputMap
      {
            byte recipient[crypto::COMPRESSED_PUBLIC_KEY_SIZE];  /** The recipients wallet address */
            int amount;                                          /** The amount of coins to be sent */
            byte sender[crypto::COMPRESSED_PUBLIC_KEY_SIZE];     /** The sender's wallet address */
            int balance;                                         /** The sender's balance after the transaction */
      };

      /**
       * @brief The input map contains critical information for the validation of the transaction
       *        like the timestamp of when the transaction was emmited, the balance the sender had before
       *        making the transaction, the public address of the sender and most importantly the transaction's
       *        digital signature.
       * 
       *        The transaction signature is obtained by signing a hash of the output map with the sender's private key
       */
      struct InputMap
      {
            time_t timestamp;                                    /** The timestamp of the transaction */
            int balance;                                         /** The sender's balance before the transaction */
            byte sender[crypto::COMPRESSED_PUBLIC_KEY_SIZE];     /** The sender's wallet address */
            byte signature[crypto::SIGNATURE_SIZE];              /** The transaction's digital signature */
      };

      /**
       * @brief The Transaction class represents a single transaction in the network.
       *        It contains the input map, the output map and the transaction ID.
       */
      class Transaction
      {
      public:
            Transaction(InputMap input_map, OutputMap output_map);
            ~Transaction();

            /** Signs the transaction with the sender's private key */
            void Sign(byte *private_key);
            /** Checks if a transaction is valid */
            bool IsValid();

            std::string ToString() const;

            /** Getters */
            [[nodiscard]] InputMap GetInputMap() const { return input_map; }
            [[nodiscard]] OutputMap GetOutputMap() const { return output_map; }
            void GetID(byte *id) { memcpy(id, this->id, crypto::SHA256_HASH_SIZE); }
      private:
            /** Get transaction hash */
            void GetHash(byte *hash);

            InputMap input_map;
            OutputMap output_map;
            byte id[crypto::SHA256_HASH_SIZE];
      };
}

#endif // !SKYNET_TRANSACTION_HPP
