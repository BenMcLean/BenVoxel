#include "Branch.h"
namespace BenVoxel {
	Branch::Branch(Branch* parent, std::uint8_t header) : Node(parent, header), children{} { }
	Branch::Branch(Branch* parent, std::istream& in) : Node(parent, in), children{} {
		std::uint8_t count = ((in.get() >> 3) & 7) + 1;
		for (std::uint8_t i = 0; i < count; i++)
			setChild(*((in.peek() & 0x80) > 0 ?
				static_cast<Node*>(new Leaf(this, in))
				: static_cast<Node*>(new Branch(this, in))));
	}
	void Branch::write(std::ostream& out) const {
		for (std::uint8_t i = 0; i < 8; i++)
			if (children[i])
				children[i]->write(out);
	}
	std::uint8_t Branch::childCount() const {
		std::uint8_t count = 0;
		for (std::uint8_t i = 0; i < 8; i++)
			if (children[i])
				count++;
		return count;
	}
	Node* Branch::getChild(std::uint8_t octant) const {
		return children[octant].get();
	}
	void Branch::setChild(Node& child) {
		children[child.getOctant()] = std::make_unique<Node>(child);
	}
	void Branch::removeChild(std::uint8_t octant) {
		children[octant] = nullptr;
		if (parent && childCount() == 0)
			parent->removeChild(this->octant);
	}
}
