#include "Branch.h"
namespace BenVoxel {
	Branch::Branch(Branch* parent, std::uint8_t octant) : Node(parent, octant), children{} { }
	Branch::Branch(Branch* parent, std::istream& in) : Node(parent, in), children{} {
		int header = in.get();
		if (header < 0)
			throw std::runtime_error("Failed to read from input stream.");
		std::uint8_t count = ((header >> 3) & 7) + 1;
		for (std::uint8_t child = 0; child < count; child++) {
			int peek = in.peek();
			if (peek < 0)
				throw std::runtime_error("Failed to read from input stream.");
			if (peek & 0x80)
				set(std::make_unique<Leaf>(this, in));
			else
				set(std::make_unique<Branch>(this, in));
		}
	}
	void Branch::write(std::ostream& out) const {
		if (!parent && !first()) {
			char bytes[15] = {};
			out.write(bytes, sizeof bytes);
			out.put(0x80);
			char bytes2[8] = {};
			out.write(bytes2, sizeof bytes2);
		}
		else {
			out.put((count() - 1) << 3 | octant);
			for (std::uint8_t octant = 0; octant < 8; octant++)
				if (children[octant])
					children[octant]->write(out);
		}
	}
	bool Branch::isLeaf() const {
		return false;
	}
	std::uint8_t Branch::count() const {
		std::uint8_t count = 0;
		for (std::uint8_t octant = 0; octant < 8; octant++)
			if (children[octant])
				count++;
		return count;
	}
	Node* Branch::first() const {
		for (std::uint8_t octant = 0; octant < 8; octant++)
			if (children[octant])
				return children[octant].get();
		return nullptr;
	}
	Node* Branch::nextValidChild(std::uint8_t previous) const {
		for (std::uint8_t octant = previous + 1; octant < 8; octant++)
			if (children[octant])
				return children[octant].get();
		return nullptr;
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
		if (parent && !first())
			parent->remove(this->octant);
	}
}
