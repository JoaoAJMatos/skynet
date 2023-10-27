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
      std::vector<skynet::Transaction> mempool_transactions = mempool.Transactions();
      std::vector<skynet::Transaction> selected_transactions;

      /** Order the transactions by fee returns */
      std::sort(mempool_transactions.begin(), mempool_transactions.end(), [](skynet::Transaction &a, skynet::Transaction &b) {
            return a.GetFeeEarnings() > b.GetFeeEarnings();
      });

      /** Pick the ones whose locktime is less than the current timestamp */
      for (auto &transaction : mempool_transactions) {
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
      block.Mine();

      /** Broadcast the block */
      callback(block);

      /** Remove the transactions from the mempool */
      for (auto &transaction : selected_transactions) {
            mempool->RemoveTransaction(transaction);
      }
}