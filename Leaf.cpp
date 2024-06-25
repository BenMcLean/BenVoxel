#include "Leaf.h"
BenVoxel::Leaf::Leaf(Node* parent, std::uint8_t header, std::array<uint8_t, 8>& data) : Node(parent, header) {
	this->data = data;
}
BenVoxel::Leaf::Leaf(Node* parent, std::istream& in) : Node(parent, in) {
	in.get();
	in.read((char*)data.data(), 8);
}
void BenVoxel::Leaf::write(std::ostream& out) const {
	out.put(0x80 | getOctant());
	out.write((const char*)data.data(), 8);
}
