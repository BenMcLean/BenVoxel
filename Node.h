#pragma once
#include <iostream>
namespace BenVoxel {
	class Branch;
	class Node {
	protected:
		std::uint8_t octant;
		Branch* parent;//Not owned
	public:
		Node(Branch* parent, std::uint8_t header);
		Node(Branch* parent, std::istream& in);
		virtual void write(std::ostream& out) const = 0;
		std::uint8_t getOctant() const;
	};
}
