#include "SparseVoxelOctree.h"
namespace BenVoxel {
	Voxel::Voxel(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t payload) : x(x), y(y), z(z), payload(payload) { }
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
	std::list<Voxel>& SparseVoxelOctree::voxels() const {
		std::list<Voxel> list = {};
		std::stack<const Branch*> stack = {};
		push(stack, &root);
		while (!stack.empty()) {
			const Branch* branch = stack.top();
			if (stack.size() == 14) {
				for (uint8_t octant = 0; octant < 8; octant++) {
					Node* node = (*branch)[octant];
					//TODO finish this method
				}
			}
		}
		return list;
	}
	void SparseVoxelOctree::push(std::stack<const Branch*>& stack, const Branch* branch) {
		while (branch) {
			stack.push(branch);
			Node* node = branch->first();
			if (node && !node->isLeaf())
				branch = (Branch*)node;
		}
	}
}
