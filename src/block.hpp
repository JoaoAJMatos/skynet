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

/** Skynet Includes */
#include <types.hpp>
#include <transaction.hpp>
#include <consensus.hpp>

namespace skynet
{
      struct BlockHeader {
            float version;                /** Version of the blockchain when the block was created */
            byte* previousHash;           /** Hash of the previous block */
            byte* merkleRoot;             /** Merkle root of the block */
            uint64_t timestamp;           /** Timestamp of the block */
            int difficultyTarget;         /** Difficulty target of the block */
            int nonce;                    /** Nonce of the block */

            BlockHeader(float version, byte* previousHash, byte* merkleRoot, uint64_t timestamp, int difficultyTarget, int nonce) {
                  this->version = version;
                  this->previousHash = previousHash;
                  this->merkleRoot = merkleRoot;
                  this->timestamp = timestamp;
                  this->difficultyTarget = difficultyTarget;
                  this->nonce = nonce;
            }
      };

      class Block
      {
      public:
            Block();
            ~Block() = default;

            
            /** 
             * @brief Returns the hash of the block
             * 
             * @return byte* The hash of the block 
             */
            byte* Hash() const;

            /** 
             * @brief Adds a transaction to the Block
             * 
             * @param transaction The transaction to be added 
             */
            void AddTransaction(Transaction transaction);

            /** Getters */
            BlockHeader GetHeaders() const;
            std::vector<Transaction> GetTransactions() const;
            int GetSize() const;

            /** 
             * @brief Returns the formatted string representation of a block 
             * 
             * @return std::string The formatted string representation of a block
             */
            std::string ToString() const;

      private:
            BlockHeader headers;                      /** Block headers */
            std::vector<Transaction> transactions;    /** Transactions in the block */
            int size;                                 /** Size of the block in bytes */
      };


      /**
       * @brief Returns the Genesis block of the Blockchain
       * 
       * @return Block The Genesis block
       */
      inline Block GenesisBlock();

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

