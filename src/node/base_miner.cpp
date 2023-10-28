//
// Created by JoaoAJMatos on 24/10/2023.
//

/** Local Includes */
#include "base_miner.hpp"

/** Skynet Includes */
#include <time.hpp>

/**
 * @brief Returns the list of transactions selected for being added to a block.
 * 
 * @param[i] mempool 
 * @return std::vector<skynet::Transaction> 
 */
static std::vector<skynet::Transaction> select_transactions(skynet::MemPool &mempool) {
      std::vector<skynet::Transaction> selected_transactions;

      /** Order the transactions by fee returns */
      std::sort(mempool.begin(), mempool.end(), [](skynet::Transaction &a, skynet::Transaction &b) {
            return a.GetFeeEarnings() > b.GetFeeEarnings();
      });

      /** Pick the ones whose locktime is less than the current timestamp */
      for (auto &transaction : mempool) {
            if (transaction.GetLocktime() < util::time::timestamp()) {
                  selected_transactions.push_back(transaction);
            }
      }

      return selected_transactions;
}

/**
 * @brief Mines a block.
 */
void skynet::Miner::Mine() {
      Block block;
      std::vector<skynet::Transaction> selected_transactions = select_transactions(*mempool);

      /** Add the transactions to the block */
      for (auto &transaction : selected_transactions) {
            block.AddTransaction(transaction);
      }

      /** Add the coinbase transaction */
      block.AddTransaction(consensus::coinbase::CreateCoinbaseTransaction(chain->Size()));

      /** Mine the block */
      //block.Mine();

      /** Broadcast the block */
      callback(block);

      /** Remove the transactions from the mempool */
      for (auto &transaction : selected_transactions) {
            TransactionID id;
            transaction.GetID(id);
            mempool->RemoveTransaction(id);
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
