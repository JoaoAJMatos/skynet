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
      typedef struct {
            float version;                /** Version of the blockchain when the block was created */
            byte* previousHash;           /** Hash of the previous block */
            byte* merkleRoot;             /** Merkle root of the block */
            uint64_t timestamp;           /** Timestamp of the block */
            int difficultyTarget;         /** Difficulty target of the block */
            int nonce;                    /** Nonce of the block */
      } BlockHeader;

      class Block
      {
      public:
            Block() = default;
            ~Block() = default;

            /** Returns the formatted string representation of a block */
            std::string ToString() const;
            /** Returns the hash of the block */
            byte* Hash() const;

            /** Returns the block's headers */
            BlockHeader GetHeaders() const;
            /** Returns the block's transactions */
            std::vector<Transaction> GetTransactions() const;
            /** Returns the block's size */
            int GetSize() const;
      private:
            BlockHeader headers;                      /** Block headers */
            std::vector<Transaction> transactions;    /** Transactions in the block */
            int size;                                 /** Size of the block in bytes */
      };

      /* Returns the Genesis block of the Blockchain */
      inline Block GenesisBlock();
      /* Returns the Genesis block header of the Blockchain */
      BlockHeader GenesisBlockHeader();
      /** Make block header with the given params */
      BlockHeader MakeBlockHeader(float version, byte* previousHash, byte* merkleRoot, uint64_t timestamp, int difficultyTarget, int nonce);

} // namespace skynet

#endif // !SKYNET_BLOCK_HPP


