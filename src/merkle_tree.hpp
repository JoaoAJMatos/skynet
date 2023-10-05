#ifndef SKYNET_MERKLE_TREE_HPP
#define SKYNET_MERKLE_TREE_HPP

#include <vector>

#include "types.hpp"

class MerkleTree
{
public:
      MerkleTree() = default;
      ~MerkleTree() = default;

      void AddLeaf(byte* leaf);
      void Build();
      void Print();

      byte* Root() const { return root_; }
private:
      std::vector<byte*> leaves_;
      std::vector<byte*> nodes_;
      byte* root_;
};


#endif // !SKYNET_MERKLE_TREE_HPP
