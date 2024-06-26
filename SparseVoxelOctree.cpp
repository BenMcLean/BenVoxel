#include "SparseVoxelOctree.h"
namespace BenVoxel {
	SparseVoxelOctree::SparseVoxelOctree(std::istream& in) {
		root = Branch(nullptr, in);
	}
	void SparseVoxelOctree::write(std::ostream& out) const {
		root.write(out);
	}
}
