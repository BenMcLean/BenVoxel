#include "Branch.h"
BenVoxel::Branch::Branch(Node* parent, std::uint8_t header, std::array<Node*, 8>& children) : Node(parent, header) {
	this->children = children;
}
BenVoxel::Branch::Branch(Node* parent, std::istream& in) : Node(parent, in) {
	std::uint8_t count = ((in.get() >> 3) & 7) + 1;
	for (std::uint8_t i = 0; i < 8; i++)
		children[i] = (in.peek() & 0x80) > 0 ?
		(Node*)(new Leaf(this, in))
		: (Node*)(new Branch(this, in));
}
void BenVoxel::Branch::write(std::ostream& out) const {
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
BenVoxel::Node* BenVoxel::Branch::getChild(std::uint8_t child) const {
	return children[child];
}
