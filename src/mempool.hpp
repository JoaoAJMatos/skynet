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

/* Skynet Includes */
#include <transaction.hpp>

namespace skynet
{
      class MemPool
      {
      public:
            MemPool() {}
            ~MemPool() {}

            /** Adds a transaction to the mempool */
            void AddTransaction(Transaction transaction);
            /** Removes a transaction from the mempool */
            void RemoveTransaction(Transaction transaction);
            /** Removes a transaction from the mempool at a given index */
            void RemoveTransactionAt(int index);
            /** Clears the mempool */
            void Clear();

            /** Returns a transaction at a given index */
            Transaction GetTransactionAt(int index);
            /** Returns a transaction with a given hash */
            Transaction GetTransactionWithHash(byte *hash);

            /** Returns the size of the mempool */
            int Size();
            std::vector<Transaction> Transactions();

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
