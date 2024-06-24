#include "Leaf.h"
void Leaf::_init(Node* parent, uint8_t header, uint64_t data) {
	Node::_init(parent, header);
	this->data = data;
}
Leaf::Leaf(Node* parent, uint8_t header, uint64_t data) : Node(parent, header) {
	this->data = data;
}
Leaf::Leaf(Node* parent, istream in) : Node(parent, in) {
	in >> data;
}
void Leaf::write(ostream out) const {
	Node::write(out);
	out.write(data);
}
