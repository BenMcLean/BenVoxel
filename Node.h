#pragma once
#include <iostream>
namespace BenVoxel {
	class Node {
	protected:
		std::uint8_t octant;
		Node* parent;
	public:
		Node(Node* parent, std::uint8_t header);
		Node(Node* parent, std::istream& in);
		virtual void write(std::ostream& out) const = 0;
		std::uint8_t getOctant() const;
	};
}
