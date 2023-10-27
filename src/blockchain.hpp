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

#ifndef SKYNET_BLOCKCHAIN_HPP
#define SKYNET_BLOCKCHAIN_HPP

/** C++ Includes */
#include <vector>

/** Skynet Includes */
#include <types.hpp>
#include <block.hpp>
#include <consensus.hpp>

namespace skynet
{
      class Chain
      {
      public:
            Chain() = default;
            ~Chain() = default;

            /* BLOCKCHAIN OPERATIONS */
            /** Adds a block to the Blockchain */
            void AddBlock(Block block);
            /** Returns the last block in the Blockchain */
            Block GetLastBlock();
            /** Returns the size of the Blockchain */
            int Size();
            /** Returns the Blocks in the Blockchain */
            std::vector<Block> Blocks();

            /* BLOCKCHAIN VALIDATION */
            /** Validates the Blockchain */
            bool IsValid();

      private:
            std::string name;
            std::vector<Block> blocks;

            /* BLOCKCHAIN FILES */
            /** Load a Blockchain from a file */
            void LoadChain(std::string file_path);
            /** Saves the Blockchain to a file */
            void SaveChain(std::string file_path);
      };
} // namespace skynet

#endif // SKYNET_BLOCKCHAIN_HPP


