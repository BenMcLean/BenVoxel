#include "Branch.h"
BenVoxel::Branch::Branch(Node* parent, std::uint8_t header, Node* children[8]) : Node(parent, header) {
	for (int i = 0; i < 8; i++)
		this->children[i] = children[i];
}
//BenVoxel::Branch::Branch(Node* parent, std::istream& in) : Node(parent, in) {
//
//}
void BenVoxel::Branch::write(std::ostream& out) const {
	Node::write(out);
	for (std::uint8_t i = 0; i < 8; i++)
		if (children[i])
			children[i]->write(out);
}
std::uint8_t BenVoxel::Branch::childCount() const {
	std::uint8_t count = 0;
	for (std::uint8_t i = 0; i < 8; i++)
		if (children[i])
			count++;
	return count;
}
BenVoxel::Node* BenVoxel::Branch::getChild(std::uint8_t& child) const {
	return children[child];
}
