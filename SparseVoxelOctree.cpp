#include "SparseVoxelOctree.h"
namespace BenVoxel {
	void SparseVoxelOctree::write(std::ostream& out) const {
		root.write(out);
	}
}
