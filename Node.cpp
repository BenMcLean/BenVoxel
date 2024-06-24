#include "Node.h"
Node::Node(Node* parent, uint8_t header) {
	this->parent = parent;
	this->header = header;
}
Node::Node(Node* parent, istream in) {
	this->parent = parent;
	in >> header;
}
void Node::write(ostream out) const {
	out.put(header);
}
uint8_t Node::octant() const {
	return header & 7;
}
bool Node::isLeaf() const {
	return (header & 0x80) > 0;
}