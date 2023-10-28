//
// Created by JoaoAJMatos on 29/10/2023.
//

/** C++ Includes */
#include <iostream>

/** Skynet Includes */
#include <crypto/sha256.hpp>

/** Local Includes */
#include "merkle_tree.hpp"

/**
 * @brief Adds a leaf to the Merkle Tree
 * 
 * @param leaf The leaf to be added
 */
void skynet::MerkleTree::AddLeaf(std::unique_ptr<byte[]> leaf) {
      leaves.push_back(std::move(leaf));
      BuildNodes();
      BuildRoot();
}

/**
 * @brief Returns the root of the Merkle Tree
 * 
 * @return std::unique_ptr<byte[]> The root of the Merkle Tree
 */
std::unique_ptr<byte[]> skynet::MerkleTree::Root() const {
      return std::unique_ptr<byte[]>(root.get());
}

/**
 * @brief Builds the nodes of the Merkle Tree
 */
void skynet::MerkleTree::BuildNodes() {
      /** If the number of leaves is odd, duplicate the last leaf */
      if (leaves.size() % 2 != 0) {
            leaves.push_back(std::unique_ptr<byte[]>(leaves.back().get()));
      }

      /** Build the nodes */
      for (int i = 0; i < leaves.size(); i += 2) {
            std::unique_ptr<byte[]> node = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
            crypto::hashing::SHA256(leaves[i].get(), crypto::hashing::SHA256_HASH_SIZE, node.get());
            crypto::hashing::SHA256(leaves[i + 1].get(), crypto::hashing::SHA256_HASH_SIZE, node.get());
            nodes.push_back(std::move(node));
      }
}

/**
 * @brief Builds the root of the Merkle Tree
 */
void skynet::MerkleTree::BuildRoot() {
      /** If the number of nodes is odd, duplicate the last node */
      if (nodes.size() % 2 != 0) {
            nodes.push_back(std::unique_ptr<byte[]>(nodes.back().get()));
      }

      /** Build the root */
      for (int i = 0; i < nodes.size(); i += 2) {
            std::unique_ptr<byte[]> node = std::make_unique<byte[]>(crypto::hashing::SHA256_HASH_SIZE);
            crypto::hashing::SHA256(nodes[i].get(), crypto::hashing::SHA256_HASH_SIZE, node.get());
            crypto::hashing::SHA256(nodes[i + 1].get(), crypto::hashing::SHA256_HASH_SIZE, node.get());
            root = std::move(node);
      }
}

/**
 * @brief Prints the nodes of the Merkle Tree
 */
void skynet::MerkleTree::PrintNodes() {
      for (int i = 0; i < nodes.size(); i++) {
            std::cout << "Node " << i << ": ";
            for (int j = 0; j < crypto::hashing::SHA256_HASH_SIZE; j++) {
                  std::cout << std::hex << (int)nodes[i][j];
            }
            std::cout << std::endl;
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