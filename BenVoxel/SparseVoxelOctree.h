#pragma once
#include <iostream>
#include <list>
#include <stack>
#include "Branch.h"
namespace BenVoxel {
	struct Voxel : Position {
		const std::uint8_t index;
		Voxel(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t index);
	};
	class SparseVoxelOctree {
	protected:
		Branch root;
		std::uint16_t sizeX;
		std::uint16_t sizeY;
		std::uint16_t sizeZ;
		static void fillStack(std::stack<Branch*>& stack, Branch* branch);
	public:
		SparseVoxelOctree();
		SparseVoxelOctree(std::uint16_t sizeX, std::uint16_t sizeY, std::uint16_t sizeZ);
		SparseVoxelOctree(std::istream& in);
		SparseVoxelOctree(std::istream& in, std::uint16_t sizeX, std::uint16_t sizeY, std::uint16_t sizeZ);
		SparseVoxelOctree(std::list<Voxel> voxels, std::uint16_t sizeX = UINT16_MAX, std::uint16_t sizeY = UINT16_MAX, std::uint16_t sizeZ = UINT16_MAX);
		SparseVoxelOctree(const SparseVoxelOctree& other);
		virtual ~SparseVoxelOctree();
		void write(std::ostream& out, bool includeSizes = true) const;
		std::uint8_t operator[](Position& position) const;
		std::uint16_t getSizeX() const;
		std::uint16_t getSizeY() const;
		std::uint16_t getSizeZ() const;
		std::uint8_t get(std::uint16_t x, std::uint16_t y, std::uint16_t z) const;
		void set(Voxel voxel);
		void set(std::uint16_t x, std::uint16_t y, std::uint16_t z, std::uint8_t index);
		std::list<Voxel> voxels() const;
		void clear();
	};
}
