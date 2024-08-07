#pragma once
#include <iostream>
#include <list>
#include <stack>
#include "Branch.h"
namespace BenVoxel {
	const struct Voxel : public Position {
	public:
		const std::uint8_t index;
		Voxel(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t index);
	};
	class SparseVoxelOctree {
	protected:
		Branch root = {};
		static void fillStack(std::stack<Branch*>& stack, Branch* branch);
	public:
		SparseVoxelOctree();
		SparseVoxelOctree(std::istream& in);
		SparseVoxelOctree(std::list<Voxel> voxels);
		SparseVoxelOctree(const SparseVoxelOctree& other);
		void write(std::ostream& out) const;
		std::uint8_t operator[](Position& position) const;
		std::uint8_t get(std::uint16_t x, std::uint16_t y, std::uint16_t z) const;
		void set(Voxel voxel);
		void set(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t index);
		std::list<Voxel> voxels() const;
		void clear();
	};
}
