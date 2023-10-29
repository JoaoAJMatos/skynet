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

/** C++ Includes */
#include <memory>

/** Skynet includes */
#include <types.hpp>
#include <crypto/ecdsa.hpp>
#include <crypto/sha256.hpp>

namespace skynet
{
      /** Type Alaises */
      using TransactionHash = byte[crypto::hashing::SHA256_HASH_SIZE];

      /**
       * @brief The TransactionInput struct represents a single input in a transaction.
       *        It contains the hash of the previous transaction's output and the index
       *        
       */
      struct TransactionInput
      {
            byte prevTransactionOutput[crypto::hashing::SHA256_HASH_SIZE]; /** The hash of the previous transaction's output (TXID) */
            int prevTransactionOutputIndex;                                /** The index of the previous transaction's output (VOUT) */
            crypto::ecdsa::PublicKey sender;                               /** The sender's wallet address */
            crypto::ecdsa::Signature signature;                            /** The signature of the sender */

            TransactionInput(byte prevTransactionOutput[crypto::hashing::SHA256_HASH_SIZE], int prevTransactionOutputIndex, crypto::ecdsa::PublicKey sender, crypto::ecdsa::Signature signature)
            {
                  memcpy(this->prevTransactionOutput, prevTransactionOutput, crypto::hashing::SHA256_HASH_SIZE);
                  this->prevTransactionOutputIndex = prevTransactionOutputIndex;
                  memcpy(this->sender, sender, crypto::ecdsa::COMPRESSED_PUBLIC_KEY_SIZE);
                  memcpy(this->signature, signature, crypto::ecdsa::SERIALIZED_SIGNATURE_SIZE);
            }
      };

      struct TransactionOutput
      {
            int value;                                          /** The amount of coins to be sent */
            crypto::ecdsa::PublicKey recipient;                 /** The recipients wallet address */

            TransactionOutput(int value, crypto::ecdsa::PublicKey recipient)
            {
                  this->value = value;
                  this->recipient = recipient;
            }
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

            /**
             * @brief Returns the hash of the transaction
             * 
             * @return std::unique_ptr<byte[]> 
             */
            std::unique_ptr<byte[]> Hash() const;

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
            time_t timestamp;                                    /** The timestamp of the transaction */
            InputMap input_map;
            OutputMap output_map;

            TransactionID id;
            time_t locktime;
            float version;
            float fee;
      };
}

#endif // SKYNET_TRANSACTION_HPP
