/**
 * @file   base_miner.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains the basic interface for a Skynet miner.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

/* Skynet Includes */
#include <block.hpp>
#include <blockchain.hpp>
#include <mempool.hpp>
#include <transaction.hpp>

/** C++ Includes */
#include <functional>

namespace skynet
{
      class Miner
      {
      public:
            /**
             * @brief Construct a new Miner object
             * @details The Miner object is used to mine blocks in the Skynet Network.
             *          It receives a mempool reference and a callback function that will be called
             *          when a block is successfully mined; this is where the block should be serialized
             *          and broadcasted to the network.
             * 
             * @param mempool 
             * @param callback 
             */
            Miner(MemPool* mempool, Chain* chain, std::function<void(Block)> callback) 
                  : mempool(mempool), chain(chain), callback(callback) 
            {

            }

            /**
             * @brief Destroy the Miner object
             */
            virtual ~Miner() {}

            /**
             * @brief Mines a block
             * @details This function should be implemented by the user.
             *          It should create a block, add transactions to it, mine it and
             *          call the callback function with the mined block.
             */
            virtual void Mine();
      private:
            MemPool* mempool;
            Chain* chain;
            std::function<void(Block)> callback;
      };
} // namespace skynet

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
