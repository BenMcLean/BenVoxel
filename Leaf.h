#pragma once
#include <iostream>
#include <array>
#include "Node.h"
namespace BenVoxel {
	class Leaf : public Node {
	protected:
		std::array<uint8_t, 8> data = {};
	public:
		Leaf(Branch* parent, std::uint8_t header, std::array<uint8_t, 8>& data);
		Leaf(Branch* parent, std::istream& in);
		void write(std::ostream& out) const override;
	};
}
