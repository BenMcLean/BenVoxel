#include "SparseVoxelOctree.h"
namespace BenVoxel {
	SparseVoxelOctree::SparseVoxelOctree(std::istream& in) {
		root = Branch(nullptr, in);
	}
	void SparseVoxelOctree::write(std::ostream& out) const {
		root.write(out);
	}
	std::uint8_t SparseVoxelOctree::get(std::uint16_t x, std::uint16_t y, std::uint16_t z) const {
		const Branch* branch = &root;
		for (std::uint8_t level = 15; level > 1; level--) {
			Node* node = (*branch)[(z >> level & 1) << 2 | (y >> level & 1) << 1 | x >> level & 1];
			if (node && !node->isLeaf())
				branch = (Branch*)node;
			else
				return 0;
		}
		Node* leaf = (*branch)[((z >> 1 & 1) << 2 | (y >> 1 & 1) << 1 | x >> 1 & 1)];
		if (leaf && leaf->isLeaf())
			return (*(Leaf*)leaf)[(z & 1) << 2 | (y & 1) << 1 | x & 1];
		return 0;
	}
}
