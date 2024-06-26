#pragma once
#include <iostream>
#include "Branch.h"
namespace BenVoxel {
	class SparseVoxelOctree {
	protected:
		Branch root = Branch(nullptr, 0);
	public:
		void write(std::ostream& out) const;
	};
}
