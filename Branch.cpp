#include "Branch.h"
namespace BenVoxel {
	Branch::Branch(Branch* parent, std::uint8_t header) : Node(parent, header), children{} { }
	Branch::Branch(Branch* parent, std::istream& in) : Node(parent, in), children{} {
		std::uint8_t count = ((in.get() >> 3) & 7) + 1;
		for (std::uint8_t i = 0; i < count; i++)
			if (in.peek() & 0x80)
				set(std::make_unique<Leaf>(this, in));
			else
				set(std::make_unique<Branch>(this, in));
	}
	void Branch::write(std::ostream& out) const {
		out.put((count() - 1) << 3 | octant);
		for (std::uint8_t i = 0; i < 8; i++)
			if (children[i])
				children[i]->write(out);
	}
	std::uint8_t Branch::count() const {
		std::uint8_t count = 0;
		for (std::uint8_t i = 0; i < 8; i++)
			if (children[i])
				count++;
		return count;
	}
	bool Branch::is() const {
		for (std::uint8_t i = 0; i < 8; i++)
			if (children[i])
				return true;
		return false;
	}
	Node* Branch::operator[](std::uint8_t octant) const {
		return children[octant].get();
	}
	void Branch::set(std::unique_ptr<Node> child) {
		if (!child)
			throw new std::invalid_argument("child should not be nullptr");
		children[child->getOctant()] = std::move(child);
	}
	void Branch::remove(std::uint8_t octant) {
		children[octant] = nullptr;
		if (parent && !is())
			parent->remove(this->octant);
	}
}
