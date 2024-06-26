#include "SparseVoxelOctree.h"
namespace BenVoxel {
	Voxel::Voxel(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t payload) : Position(x, y, z), payload(payload) { }
	SparseVoxelOctree::SparseVoxelOctree(std::istream& in) {
		root = Branch(nullptr, in);
	}
	void SparseVoxelOctree::write(std::ostream& out) const {
		root.write(out);
	}
	std::uint8_t SparseVoxelOctree::operator[](Position& position) const {
		return get(position.x, position.y, position.z);
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
		std::stack<Branch*> stack = {};
		push(stack, const_cast<Branch*>(&root));
		while (!stack.empty()) {
			Branch* branch = stack.top();
			if (stack.size() == 14) {
				for (uint8_t octant = 0; octant < 8; octant++) {
					Node* node = (*branch)[octant];
					if (node && node->isLeaf()) {
						Leaf* leaf = (Leaf*)node;
						Position position = leaf->position();
						for (uint8_t index = 0; index < 8; index++) {
							uint8_t payload = (*leaf)[index];
							if (payload)
								list.push_back(Voxel(
									position.x + (index & 1),
									position.y + ((index << 1) & 1),
									position.z + ((index << 2) & 1),
									payload));
						}
					}
				}
			}
			Branch* parent = branch->getParent();
			if (parent) {
				Node* next = parent->next(branch->getOctant());
				if (next && !next->isLeaf())
					push(stack, (Branch*)next);
			}
		}
		return list;
	}
	void SparseVoxelOctree::push(std::stack<Branch*>& stack, Branch* branch) {
		while (branch) {
			stack.push(branch);
			Node* node = branch->first();
			if (node && !node->isLeaf())
				branch = (Branch*)node;
		}
	}
}
