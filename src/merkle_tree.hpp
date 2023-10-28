/**
 * @file    merkle_tree.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the Merkle Tree class definition. 
 * 
 * @details A Merkle Tree is a data structure that is used to verify the integrity of data.
 *          In skynet, Merkle Trees are used to verify the integrity of the transactions in a block.
 *
 * @version 0.1
 * @date 2023-10-29
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_MERKLE_TREE_HPP
#define SKYNET_MERKLE_TREE_HPP

/** C++ Includes */
#include <vector>
#include <memory>

/** Skynet Includes */
#include <types.hpp>

namespace skynet
{
      class MerkleTree
      {
      public:
            MerkleTree() = default;
            ~MerkleTree() = default;

            /**
             * @brief Adds a leaf to the Merkle Tree
             * 
             * @param leaf The leaf to be added
             */
            void AddLeaf(std::unique_ptr<byte[]> leaf);

            /**
             * @brief Returns the root of the Merkle Tree
             * 
             * @return std::unique_ptr<byte[]> The root of the Merkle Tree
             */
            std::unique_ptr<byte[]> Root() const;

      private:
            /** Member variables */
            std::vector<std::unique_ptr<byte[]>> leaves;
            std::vector<std::unique_ptr<byte[]>> nodes;
            std::unique_ptr<byte[]> root;

            /** Member functions */
            void BuildNodes();
            void BuildRoot();
            void PrintNodes();
      };
} // namespace skynet


#endif // SKYNET_MERKLE_TREE_HPP

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
