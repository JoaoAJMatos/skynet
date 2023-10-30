/**
 * @file    block.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the Block class definition.
 *          A Block is a data structure that represents a single block
 *          in the Blockchain. It contains the block's data, the hash
 *          of the previous block, the merkle root, the block's hash,
 *          the timestamp and the nonce.
 *
 * @date    2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_BLOCK_HPP
#define SKYNET_BLOCK_HPP

/** C++ Includes */
#include <vector>
#include <memory>

/** Skynet Includes */
#include <types.hpp>
#include <transaction.hpp>
#include <consensus.hpp>

namespace skynet
{
      /** Constants */
      constexpr int MAX_TRANSACTIONS_PER_BLOCK = 1000;

      struct BlockHeader {
            float version;                         /** Version of the blockchain when the block was created */
            std::unique_ptr<byte[]> prevHash;      /** Hash of the previous block */
            std::unique_ptr<byte[]> merkleRoot;    /** Merkle root of the block */
            std::time_t timestamp;                 /** Timestamp of the block */
            int difficultyTarget;                  /** Difficulty target of the block */
            int nonce;                             /** Nonce of the block */

            /** Constructors */
            BlockHeader() = default;

            BlockHeader(float version, std::unique_ptr<byte[]> prevHash, std::unique_ptr<byte[]> merkleRoot, std::time_t timestamp, int difficultyTarget, int nonce) {
                  this->version = version;
                  this->prevHash = std::move(prevHash);
                  this->merkleRoot = std::move(merkleRoot);
                  this->timestamp = timestamp;
                  this->difficultyTarget = difficultyTarget;
                  this->nonce = nonce;
            }

            BlockHeader(const BlockHeader &header) {
                  version = header.version;
                  prevHash = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
                  std::copy(header.prevHash.get(), header.prevHash.get() + crypto::hashing::SHA256_HASH_SIZE, prevHash.get());
                  merkleRoot = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
                  std::copy(header.merkleRoot.get(), header.merkleRoot.get() + crypto::hashing::SHA256_HASH_SIZE, merkleRoot.get());
                  timestamp = header.timestamp;
                  difficultyTarget = header.difficultyTarget;
                  nonce = header.nonce;
            }

            BlockHeader &operator=(const BlockHeader &header) {
                  version = header.version;
                  prevHash = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
                  std::copy(header.prevHash.get(), header.prevHash.get() + crypto::hashing::SHA256_HASH_SIZE, prevHash.get());
                  merkleRoot = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
                  std::copy(header.merkleRoot.get(), header.merkleRoot.get() + crypto::hashing::SHA256_HASH_SIZE, merkleRoot.get());
                  timestamp = header.timestamp;
                  difficultyTarget = header.difficultyTarget;
                  nonce = header.nonce;
                  return *this;
            }
      };

      class Block
      {
      public:
            Block();
            Block(BlockHeader header, std::vector<Transaction> transactions);
            ~Block() = default;

            /** 
             * @brief Returns the hash of the block
             *
             * @return std::unique_ptr<byte[]> The hash of the block 
             */
            std::unique_ptr<byte[]> Hash() const;

            /** 
             * @brief Adds a transaction to the Block
             * 
             * @param transaction The transaction to be added
             * @throws std::runtime_error If the block is full
             */
            void AddTransaction(Transaction transaction);

            /** 
             * @brief Adds a Coinbase transaction to the Block
             * 
             * @param minerAddress The address of the miner
             * @throws std::runtime_error If the block is full
             */
            void AddCoinbaseTransaction(std::string minerAddress);

            /** 
             * @brief Returns the formatted string representation of a block 
             * 
             * @return std::string The formatted string representation of a block
             */
            std::string ToString() const;

            /**
            * @brief Returns the Genesis block of the Blockchain
            * 
            * @return Block The Genesis block
            */
            static std::unique_ptr<Block> GenesisBlock();

            /** Getters */
            BlockHeader GetHeader() const { return header; }
            std::vector<Transaction> GetTransactions() const { return transactions; }
            int GetTransactionCount() const { return transactionCount; }

            /** Setters */
            void SetHeader(BlockHeader header) { this->header = header; }
            void SetTransactions(std::vector<Transaction> transactions) { this->transactions = transactions; }

      private:
            BlockHeader header;                       /** The block header */
            std::vector<Transaction> transactions;    /** Transactions in the block */
            int transactionCount;                     /** Number of transactions in the block */
      };

      /**
       * @brief Calculates the Merkle Root of a vector of transactions
       * 
       * @param transactions The vector of transactions
       * @return std::unique_ptr<byte[]> The Merkle Root of the vector of transactions
       * @throws std::runtime_error If the vector of transactions is empty
       */
      std::unique_ptr<byte[]> CalculateMerkleRoot(std::vector<Transaction> transactions);

} // namespace skynet

#endif // SKYNET_BLOCK_HPP

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

