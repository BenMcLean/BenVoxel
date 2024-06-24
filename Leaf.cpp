#include "Leaf.h"
BenVoxel::Leaf::Leaf(Node* parent, std::uint8_t header, std::uint8_t(&data)[8]) : Node(parent, header) {
	for (std::uint8_t i = 0; i < 8; i++)
		this->data[i] = data[i];
}
BenVoxel::Leaf::Leaf(Node* parent, std::istream& in) : Node(parent, in) {
	for (std::uint8_t i = 0; i < 8; i++)
		data[i] = in.get();
}
void BenVoxel::Leaf::write(std::ostream& out) const {
	Node::write(out);
	for (std::uint8_t i = 0; i < 8; i++)
		out.put(data[i]);
}
