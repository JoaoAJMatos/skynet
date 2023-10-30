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

            /* BLOCKCHAIN VALIDATION */
            /** Validates the Blockchain */
            bool IsValid();

            /* BLOCKCHAIN GETTERS */
            /** Returns the Blocks in the Blockchain */
            std::vector<Block> GetBlocks();
            /** Returns the last block in the Blockchain */
            Block GetLastBlock();
            /** Returns the size of the Blockchain */
            int Size();

      private:
            std::string name;
            std::vector<std::unique_ptr<Block>> blocks;

            /* BLOCKCHAIN FILES */
            /** Load a Blockchain from a file */
            void LoadChain(std::string file_path);
            /** Saves the Blockchain to a file */
            void SaveChain(std::string file_path);
      };
} // namespace skynet

#endif // SKYNET_BLOCKCHAIN_HPP

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
