/**
 * @file    consensus.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file defines some of the consensus rules that
 *          Skynet follows.
 *
 * @date    2023-09-28
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_CONSENSUS_HPP
#define SKYNET_CONSENSUS_HPP

/** C++ Includes */
#include <ctime>

namespace skynet::consensus
{
      /** The version of the blockchain */
      constexpr float VERSION = 1.0;
      /** The initial block difficulty */
      constexpr int INITIAL_DIFFICULTY = 1;
      /** The Mining rate (blocks/hour) */
      constexpr int MINING_RATE = 60;
      /** Halving frequency */
      constexpr int DIFFICULTY_ADJUSTMENT_INTERVAL = 2016;
      /** The initial block subsidy */
      constexpr int INITIAL_SUBSIDY = 50;
      /** The maximum amount of transactions per block */
      constexpr int MAX_TRANSACTIONS_PER_BLOCK = 10;
      /** The maximum block size in bytes */
      constexpr int MAX_BLOCK_SIZE = 1000000;
      /** Max coins in a transaction */
      constexpr int MAX_COINS_PER_TRANSACTION = 1000000;
      /** Coin */
      constexpr int COIN = 100000000; // 1 SKY = 100000000 COINS

      /**
       * @brief Returns the mining reward of a block at a given height
       * 
       * @param height The height of the block
       * @return int The difficulty of the block
       */
      int GetBlockSubsidy(int height) {
            return INITIAL_SUBSIDY >> (height / DIFFICULTY_ADJUSTMENT_INTERVAL);
      }

      /**
       * @brief Returns the expected difficulty of a block given the last difficulty
       *        and time the last block was mined and the current time in order to
       *        keep the mining rate constant.
       * 
       * @param lastDifficulty The difficulty of the last block
       * @param lastTimestamp The timestamp of the last block
       * @param currentTimestamp The current timestamp
       */
      int AdjustDifficulty(int lastDifficulty, std::time_t lastTimestamp, std::time_t currentTimestamp) {
            int timeExpected = MINING_RATE * DIFFICULTY_ADJUSTMENT_INTERVAL;
            int timeTaken = currentTimestamp - lastTimestamp;
            
            if (timeTaken < timeExpected / 2) return lastDifficulty + 1;
            else if (timeTaken > timeExpected * 2) return lastDifficulty - 1;

            return lastDifficulty;
      }
}

#endif // SKYNET_CONSENSUS_HPP

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
