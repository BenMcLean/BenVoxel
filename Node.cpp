#include "Node.h"
BenVoxel::Node::Node(Node* parent, std::istream& in) : Node(parent, in.peek()) { }
BenVoxel::Node::Node(Node* parent, std::uint8_t header) {
	this->parent = parent;
	this->octant = header & 7;
}
std::uint8_t BenVoxel::Node::getOctant() const {
	return octant;
}
//bool BenVoxel::Node::isLeaf() const {
//	return (header & 0x80) > 0;
//}
