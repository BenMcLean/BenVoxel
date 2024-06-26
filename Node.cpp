#include "Node.h"
namespace BenVoxel {
	Position::Position(std::uint16_t x, std::uint16_t y, std::uint16_t z) : x(x), y(y), z(z) { }
	Node::Node(Branch* parent, std::istream& in) : Node(parent, in.peek()) { }
	Node::Node(Branch* parent, std::uint8_t header) {
		this->parent = parent;
		this->octant = header & 7;
	}
	std::uint8_t Node::getOctant() const {
		return octant;
	}
}
//bool BenVoxel::Node::isLeaf() const {
//	return (header & 0x80) > 0;
//}
