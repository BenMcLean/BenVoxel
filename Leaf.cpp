#include "Leaf.h"
void Leaf::_init(Node* parent, std::uint8_t header, std::uint64_t data) {
	Node::_init(parent, header);
	this->data = data;
}
Leaf::Leaf(Node* parent, std::uint8_t header, std::uint64_t data) : Node(parent, header) {
	this->data = data;
}
Leaf::Leaf(Node* parent, std::istream& in) : Node(parent, in) {
	in >> data;
}
void Leaf::write(std::ostream& out) const {
	Node::write(out);
	BinaryReadWrite::writeU64(out, data);
}
