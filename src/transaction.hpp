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
            crypto::ecdsa::PublicKey recipient;                  /** The recipients wallet address */
            int amount;                                          /** The amount of coins to be sent */
            crypto::ecdsa::PublicKey sender;                     /** The sender's wallet address */
            int balance;                                         /** The sender's balance after the transaction */

            /** Serializing/Deserializing */
            void ToBytes(byte *bytes);
            void FromBytes(byte *bytes);
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
            crypto::ecdsa::PublicKey sender;                     /** The sender's wallet address */
            crypto::ecdsa::Signature signature;                  /** The transaction's digital signature */

            /** Serializing/Deserializing */
            void ToBytes(byte *bytes);
            void FromBytes(byte *bytes);
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

            /**
             * @brief Checks if a transaction is valid
             * @details Validates the OutputMap and the InputMap
             * 
             * @return true 
             * @return false 
             */
            bool IsValid();

            /**
             * @brief Returns the formatted string representation of a transaction
             * 
             * @return std::string 
             */
            std::string ToString() const;

            /** Getters */
            [[nodiscard]] InputMap GetInputMap() const { return input_map; }
            [[nodiscard]] OutputMap GetOutputMap() const { return output_map; }
            void GetID(byte *id) { memcpy(id, this->id, crypto::hashing::SHA256_HASH_SIZE); }
            [[nodiscard]] time_t GetLocktime() const { return locktime; }
            [[nodiscard]] float GetVersion() const { return version; }
            [[nodiscard]] float GetFee() const { return fee; }

            /**
             * @brief Calculates the fee earnings of the miner
             * 
             * @return int 
             */
            int GetFeeEarnings();
      private:
            InputMap input_map;
            OutputMap output_map;

            byte id[crypto::hashing::SHA256_HASH_SIZE];
            time_t locktime;
            float version;
            float fee;

            /** Get transaction hash */
            void Hash(byte *hash);
      };
}

#endif // SKYNET_TRANSACTION_HPP
