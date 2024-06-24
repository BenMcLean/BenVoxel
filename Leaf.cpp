#include "Leaf.h"
BenVoxel::Leaf::Leaf(Node* parent, std::uint8_t header, std::uint64_t data) : Node(parent, header) {
	this->data = data;
}
BenVoxel::Leaf::Leaf(Node* parent, std::istream& in) : Node(parent, in) {
	data = BinaryReadWrite::readU64(in);
}
void BenVoxel::Leaf::write(std::ostream& out) const {
	Node::write(out);
	BinaryReadWrite::writeU64(out, data);
}
