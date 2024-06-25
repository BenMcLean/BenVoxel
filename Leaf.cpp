#include "Leaf.h"
namespace BenVoxel {
	Leaf::Leaf(Branch* parent, std::uint8_t header, std::array<uint8_t, 8>& data) : Node(parent, header), data{} {
		this->data = data;
	}
	Leaf::Leaf(Branch* parent, std::istream& in) : Node(parent, in), data{} {
		in.get();
		in.read((char*)data.data(), 8);
	}
	void Leaf::write(std::ostream& out) const {
		out.put(0x80 | octant);
		out.write((const char*)data.data(), 8);
	}
}
