//
// Created by JoaoAJMatos on 29/10/2023.
//

/** Local Includes */
#include "blockchain.hpp"


//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Sends the transactions inside a block to the mempool
 *
 * @details Used when a fork is resolved to send the transactions
 *          that were in the block that got replaced back to the mempool
 *          so they can be added to a block again.
 *
 * @param block
 * @param mempool
 */
static void send_block_transactions_back_to_mempool(
       const skynet::Block& block,
       const std::shared_ptr<skynet::MemPool>& mempool
) {
      for (const auto& transaction : block.GetTransactions()) {
            mempool->AddTransaction(transaction);
      }
}

/**
 * @brief Checks if the given block corresponds to the Genesis block
 *
 * TODO: Maybe make this more secure? Like asking the network for the Genesis block?
 *
 * @param chain
 * @param block
 * @return
 */
static inline bool is_genesis_block(
       const std::vector<std::unique_ptr<skynet::Block>>& chain,
       const skynet::Block& block
) {
      return chain.empty() && block.Height() == 0;
}

/**
 * @brief Pushes a block into the given chain if it has valid content
 *
 * @param chain
 * @param block
 * @throws skynet::ChainException If the block is invalid
 */
static inline void push_block_if_valid(
       std::vector<std::unique_ptr<skynet::Block>>& chain,
       const skynet::Block& block
) {
      if (!block.HasValidContent()) {
            throw skynet::ChainException("Invalid block");
      }

      chain.push_back(std::make_unique<skynet::Block>(block));
}

/**
 * @brief Checks if two hashes match
 *
 * @param hash1
 * @param hash2
 * @return
 */
static inline bool hashes_do_match(
       const std::unique_ptr<byte[]>& hash1,
       const std::unique_ptr<byte[]>& hash2
) {
      return crypto::hashing::SHA256::CompareHash(hash1.get(), hash2.get());
}

//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Adds a block to the Blockchain
 *
 * @details Performs the necessary checks and adds the block to the Blockchain.
 *
 * @param block
 * @throws std::runtime_error If the block is invalid
 */
void skynet::Chain::AddBlock(const skynet::Block& block) {
      /** Genesis block */
      if (is_genesis_block(blocks, block)) {
            push_block_if_valid(blocks, block); // Can throw ChainException
            return;
      }

      /** Normal cases */
      if (BlockHasExpectedHeight(block) && BlockExtendsMainChain(block)) {
            push_block_if_valid(blocks, block); // Can throw ChainException
            return;
      } else if (BlockIsFork(block)) {
            HandleForkResolution(block);
            return;
      }

      throw ChainException("Invalid block");
}

//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if a Block has the expected height given the last block in the chain
 *
 * @param newBlock
 * @return
 */
inline bool skynet::Chain::BlockHasExpectedHeight(const skynet::Block &newBlock) const {
      return newBlock.Height() == GetLastBlock().Height() + 1;
}

/**
 * @brief Checks if a Block extends the main chain by checking the previous hash
 *        of the new block and the hash of the last block in the chain
 *
 * @param newBlock
 * @return
 */
inline bool skynet::Chain::BlockExtendsMainChain(const skynet::Block &newBlock) const {
      return hashes_do_match(newBlock.GetHeader().prevHash, GetLastBlock().Hash());
}

/**
 * @brief Checks if the incoming block creates a fork of the main chain
 *
 * @details If both blocks have the same height, they are both trying to extend the main chain
 *          at the same index. We must check if the blocks are different, and if they are, we
 *          should handle the fork resolution.
 *
 * @param newBlock
 * @return
 */
bool skynet::Chain::BlockIsFork(const Block& newBlock) const {
      const Block& lastBlock = GetLastBlock();

      if (lastBlock.Height() == newBlock.Height() && lastBlock != newBlock && newBlock.HasValidContent())
            return true;

      return false;
}

/**
 * @brief Handles the resolution of the blockchain fork
 *
 * @details If the new block has a higher difficulty than the last block in the main chain,
 *          we should replace the main chain with the new block. If both blocks have the same
 *          difficulty, we should wait for the next block to be mined and adopt the longest
 *          chain as the main chain.
 *
 *          The transactions present in the block(s) that got replaced must be sent back to the
 *          mempool to be added again to a block.
 *
 * @param block
 */
void skynet::Chain::HandleForkResolution(const skynet::Block& block) {
      const Block& blockToBeReplaced = GetLastBlock();

      if (block.GetDifficultyTarget() > blockToBeReplaced.GetDifficultyTarget()) {
            /** Replace the main chain with the new block */
            blocks.pop_back();
            blocks.push_back(std::make_unique<Block>(block));
            send_block_transactions_back_to_mempool(blockToBeReplaced, this->mempool);
      } else if (block.GetDifficultyTarget() == blockToBeReplaced.GetDifficultyTarget()) {
            /** Add the block to the orphan blocks */
            this->orphans.push_back(std::make_unique<Block>(block));
      }
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
