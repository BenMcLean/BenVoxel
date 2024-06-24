#include "Node.h"
void BenVoxel::Node::_init(Node* parent, std::uint8_t header) {
	this->parent = parent;
	this->header = header;
}
BenVoxel::Node::Node(Node* parent, std::istream& in) {
	_init(parent, in.get());
}
BenVoxel::Node::Node(Node* parent, std::uint8_t header) {
	_init(parent, header);
}
void BenVoxel::Node::write(std::ostream& out) const {
	out.put(header);
}
std::uint8_t BenVoxel::Node::octant() const {
	return header & 7;
}
bool BenVoxel::Node::isLeaf() const {
	return (header & 0x80) > 0;
}
