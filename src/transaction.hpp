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
            TransactionHash prevTransactionOutput;        /** The hash of the previous transaction's output (TXID) */
            int prevTransactionOutputIndex;               /** The index of the previous transaction's output (VOUT) */
            crypto::ecdsa::PublicKey sender;              /** The sender's wallet address */
            crypto::ecdsa::Signature signature;           /** The signature of the sender */
            int sequence;                                 /** The sequence number */

            /** Constructor */
            TransactionInput(
                  byte prevTransactionOutput[crypto::hashing::SHA256_HASH_SIZE], 
                  int prevTransactionOutputIndex, 
                  crypto::ecdsa::PublicKey sender, 
                  crypto::ecdsa::Signature signature,
                  int sequence
            ) 
            {
                  memcpy(this->prevTransactionOutput, prevTransactionOutput, crypto::hashing::SHA256_HASH_SIZE);
                  this->prevTransactionOutputIndex = prevTransactionOutputIndex;
                  memcpy(this->sender, sender, crypto::ecdsa::COMPRESSED_PUBLIC_KEY_SIZE);
                  memcpy(this->signature, signature, crypto::ecdsa::SERIALIZED_SIGNATURE_SIZE);
                  this->sequence = sequence;
            }
      };

      struct TransactionOutput
      {
            int value;                                          /** The amount of coins to be sent */
            crypto::ecdsa::PublicKey recipient;                 /** The recipients wallet address */

            TransactionOutput(int value, crypto::ecdsa::PublicKey recipient) {
                  this->value = value;
                  memcpy(this->recipient, recipient, crypto::ecdsa::COMPRESSED_PUBLIC_KEY_SIZE);
            }
      };

      /**
       * @brief The Transaction class represents a single transaction in the network.
       *        It contains the input map, the output map and the transaction ID.
       */
      class Transaction
      {
      public:
            Transaction(TransactionInput input, TransactionOutput output);
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
             * @brief Returns the hash of the transaction
             * 
             * @return std::unique_ptr<byte[]> 
             */
            std::unique_ptr<byte[]> Hash() const;
            
            /**
             * @brief Calculates the fee earnings of the miner
             * 
             * @param transaction
             * @return int 
             */
            static int CalculateFee(Transaction transaction);

            /**
             * @brief Returns the formatted string representation of a transaction
             * 
             * @return std::string 
             */
            std::string ToString() const;

            /** Operators */
            bool operator==(const Transaction &transaction) const;
            bool operator!=(const Transaction &transaction) const;

            /** Getters */
            [[nodiscard]] TransactionInput GetInput() const { return input; }
            [[nodiscard]] TransactionOutput GetOutput() const { return output; }
            [[nodiscard]] time_t GetLocktime() const { return locktime; }
            [[nodiscard]] float GetVersion() const { return version; }
            
      private:
            time_t timestamp;             /** The timestamp of the transaction */
            TransactionInput input;       /** The input of the transaction */
            TransactionOutput output;     /** The output of the transaction */
            time_t locktime;              /** The time when the transaction can be added to a block */
            float version;                /** The version of the protocol when the transaction was created */
      };
}

#endif // SKYNET_TRANSACTION_HPP
