/**
 * @file   mempool.hpp
 * @author JoaoAJMatos
 *
 * @brief The header file contains the definitions for the mempool.
 *        The mempool is a data structure that contains all the transactions
 *        that are waiting to be added to a block.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

/* C++ Includes */
#include <stdexcept>
#include <vector>
#include <memory>

/* Skynet Includes */
#include <transaction.hpp>

namespace skynet
{
      class MemPool
      {
      public:
            MemPool() {}
            ~MemPool() {}

            /** Iterators */
            std::vector<Transaction>::iterator begin() { return transactions.begin(); }
            std::vector<Transaction>::iterator end() { return transactions.end(); }

            /** 
             * @brief Adds a transaction to the mempool 
             *
             * @param transaction The transaction to be added 
             */
            void AddTransaction(Transaction transaction);
            
            /** 
             * @brief Removes a transaction from the mempool
             * 
             * @param transaction_id The ID of the transaction to be removed
             * @throws std::runtime_error If the transaction is not found
             */
            void RemoveTransaction(TransactionID transaction_id);

            /** 
             * @brief Returns a transaction with a given ID 
             * 
             * @param transaction_id The ID of the transaction to be returned
             * @return Transaction The transaction with the given ID
             */
            Transaction GetTransaction(TransactionID transaction_id);

            /** 
             * @brief Get the vector of transactions
             * 
             * @return std::vector<Transaction> The vector of transactions 
             */
            std::vector<Transaction> GetTransactions() const { return transactions; }

            /** 
             * @brief Returns the size of the mempool 
             */
            int size() const { return transactions.size(); }

            /** 
             * @brief Returns true if the mempool is empty, false otherwise 
             */
            bool empty() const { return transactions.empty(); }

      private:
            std::vector<Transaction> transactions;
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
