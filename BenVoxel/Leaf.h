#pragma once
#include <iostream>
#include <algorithm>
#include <array>
#include "Node.h"
#include "Branch.h"
namespace BenVoxel {
	class Leaf : public Node {
	protected:
		std::array<std::uint8_t, 8> data = {};
	public:
		Leaf(Branch* parent, std::uint8_t octant);
		Leaf(Branch* parent, std::uint8_t octant, std::uint8_t color);
		Leaf(Branch* parent, std::istream& in);
		void write(std::ostream& out) const override;
		std::uint8_t operator[](std::uint8_t octant) const;
		void set(std::uint8_t octant, std::uint8_t index);
	};
}
