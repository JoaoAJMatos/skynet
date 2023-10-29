//
// Created by JoaoAJMatos on 29/10/2023.
//

/** Skynet Includes */
#include <time.hpp>
#include <consensus.hpp>
#include <merkle_tree.hpp>

/** Local Include */
#include "block.hpp"


/** 
* @brief Returns the hash of the block
*
* @return std::unique_ptr<byte[]> The hash of the block 
*/
std::unique_ptr<byte[]> skynet::Block::Hash() const {
      auto hash = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
      auto data = std::make_unique<byte[]>(sizeof(BlockHeader) + this->transactionCount * sizeof(Transaction));

      /** Combine all the block's data into a single byte array */
      memcpy(data.get(), &this->header, sizeof(BlockHeader));
      memcpy(data.get() + sizeof(BlockHeader), this->transactions.data(), this->transactionCount * sizeof(Transaction));

      /** Hash the contents of the block */
      crypto::hashing::SHA256(data.get(), sizeof(BlockHeader) + this->transactionCount * sizeof(Transaction), hash.get());

      /** Return the hash */
      return hash;
}

/** 
* @brief Adds a transaction to the Block
* 
* @param transaction The transaction to be added
* @throws std::runtime_error If the block is full
*/
void skynet::Block::AddTransaction(Transaction transaction) {
      if (this->transactionCount == MAX_TRANSACTIONS_PER_BLOCK) {
            throw std::runtime_error("Block is full");
      }

      this->transactions.push_back(transaction);
      this->transactionCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////////

inline skynet::Block skynet::Block::GenesisBlock() {
      std::vector<Transaction> transactions;

      /** Create the coinbase transaction */
      transactions.push_back(consensus::coinbase::CreateCoinbaseTransaction(0));

      return Block(
            BlockHeader(
                  consensus::VERSION,                                               // Version
                  std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE),      // Previous hash
                  CalculateMerkleRoot(transactions),                                // Merkle root
                  util::time::timestamp(),                                          // Timestamp
                  consensus::INITIAL_DIFFICULTY,                                    // Difficulty target
                  0                                                                 // Nonce
            ), 
            transactions
      );
}

//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Returns the merkle root of a vector of transactions
 * 
 * @param transactions The vector of transactions
 * @return std::unique_ptr<byte[]> The merkle root of the vector of transactions
 */
std::unique_ptr<byte[]> skynet::CalculateMerkleRoot(std::vector<Transaction> transactions) {
      if (transactions.size() == 0) {
            return std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
      }

      MerkleTree tree;
      for (auto& transaction : transactions) {
            tree.AddLeaf(transaction.Hash());
      }
      return tree.Root();
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