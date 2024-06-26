#pragma once
#include <iostream>
#include "Branch.h"
namespace BenVoxel {
	class SparseVoxelOctree {
	protected:
		Branch root = Branch(nullptr, 0);
	public:
		SparseVoxelOctree(std::istream& in);
		void write(std::ostream& out) const;
		std::uint8_t get(std::uint16_t x, std::uint16_t y, std::uint16_t z) const;
	};
}
