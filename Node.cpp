#include "Node.h"
namespace BenVoxel {
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
