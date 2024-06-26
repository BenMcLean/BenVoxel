#include "Leaf.h"
namespace BenVoxel {
	Leaf::Leaf(Branch* parent, std::uint8_t header, std::array<std::uint8_t, 8>& data) : Node(parent, header), data{} {
		this->data = data;
	}
	Leaf::Leaf(Branch* parent, std::istream& in) : Node(parent, in), data{} {
		in.get();
		in.read((char*)data.data(), 8);
		set(0, data[0]);//Make sure this Leaf gets deleted if it's empty
	}
	void Leaf::write(std::ostream& out) const {
		out.put(0x80 | octant);
		out.write((const char*)data.data(), 8);
	}
	bool Leaf::isLeaf() const {
		return true;
	}
	std::uint8_t Leaf::operator[](std::uint8_t octant) const {
		return data[octant];
	}
	void Leaf::set(std::uint8_t octant, std::uint8_t payload) {
		data[octant] = payload;
		if (parent && data == std::array<std::uint8_t, 8>{})//This checks for all zeroes and modern compilers won't allocate a new array
			parent->remove(octant);
	}
}
