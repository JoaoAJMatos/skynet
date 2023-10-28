//
// Created by JoaoAJMatos on 29/10/2023.
//

/** C++ Includes */
#include <algorithm>

/** Local Includes */
#include "mempool.hpp"


/** 
* @brief Adds a transaction to the mempool 
*
* @param transaction The transaction to be added 
*/
void skynet::MemPool::AddTransaction(Transaction transaction) {
      transactions.push_back(transaction);
}

/** 
* @brief Removes a transaction from the mempool
* 
* @param transaction_id The ID of the transaction to be removed
* @throws std::runtime_error If the transaction is not found
*/
void skynet::MemPool::RemoveTransaction(TransactionID transaction_id) {
      TransactionID id;

      for (auto& transaction : transactions) {
            transaction.GetID(id);
            if (crypto::hashing::SHA256::CompareHash(id, transaction_id)) {
                  transactions.erase(std::remove(transactions.begin(), transactions.end(), transaction), transactions.end());
                  return;
            }
      }

      throw std::runtime_error("Transaction not found");
}

/** 
* @brief Returns a transaction with a given ID 
* 
* @param transaction_id The ID of the transaction to be returned
* @return Transaction The transaction with the given ID
*/
skynet::Transaction skynet::MemPool::GetTransaction(TransactionID transaction_id) {
      TransactionID id;

      for (auto& transaction : transactions) {
            transaction.GetID(id);
            if (crypto::hashing::SHA256::CompareHash(id, transaction_id)) {
                  return transaction;
            }
      }

      throw std::runtime_error("Transaction not found");
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