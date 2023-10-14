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

namespace skynet
{
      class Block
      {
      public:
            Block() = default;
            ~Block() = default;
      private:
            byte* data;
            byte* hash;
            byte* previousHash;
            byte* merkleRoot;
            std::vector<Transaction> transactions;
            int nonce;
            int difficulty;
            uint64_t timestamp;
      };

      /* Returns the Genesis block of the Blockchain */
      inline Block GenesisBlock();

} // namespace skynet

#endif // !SKYNET_BLOCK_HPP


