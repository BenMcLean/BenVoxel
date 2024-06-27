#pragma once
#include <iostream>
#include <list>
#include <stack>
#include "Branch.h"
namespace BenVoxel {
	const struct Voxel : public Position {
	public:
		const std::uint8_t payload;
		Voxel(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t payload);
	};
	class SparseVoxelOctree {
	protected:
		Branch root = Branch(nullptr, 0);
		static void push(std::stack<Branch*>& stack, Branch* branch);
	public:
		SparseVoxelOctree() = default;
		SparseVoxelOctree(std::istream& in);
		void write(std::ostream& out) const;
		std::uint8_t operator[](Position& position) const;
		std::uint8_t get(std::uint16_t x, std::uint16_t y, std::uint16_t z) const;
		void set(Voxel voxel);
		void set(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t payload);
		std::list<Voxel>& voxels() const;
	};
}
