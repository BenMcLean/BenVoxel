#include "Branch.h"
namespace BenVoxel {
	Branch::Branch() : Node(nullptr, 0), children{} {}
	Branch::Branch(Branch* parent, std::uint8_t octant) : Node(parent, octant & 0b111), children{} {}
	Branch::Branch(Branch* parent, std::uint8_t octant, std::uint8_t color) : Node(parent, octant & 0b111), children{}
	{
		expandCollapsed(color);
	}
	Branch::Branch(Branch* parent, std::istream& in) : Node(parent, in), children{} {
		std::uint8_t header = readByte(in, "Failed to read branch header byte from input stream.");
		switch (header & TYPE_MASK) {
		case BRANCH_REGULAR: {
			std::uint8_t count = ((header >> 3) & 0b111) + 1;
			for (std::uint8_t child = 0; child < count; child++)
				if (peekByte(in) >> 7)//Check if it's a leaf (both 2-byte and 8-byte start with 1)
					set(std::make_unique<Leaf>(this, in));
				else
					set(std::make_unique<Branch>(this, in));
			break;
		}
		case BRANCH_COLLAPSED: {
			expandCollapsed(readByte(in, "Failed to read collapsed branch value from input stream."));
			break;
		}
		default:
			throw std::runtime_error("Invalid branch type in header");
		}
	}
	void Branch::expandCollapsed(std::uint8_t color) {
		if (depth() == 15)
			for (std::uint8_t octant = 0; octant < 8; octant++)
				set(std::make_unique<Leaf>(this, octant, color));
		else
			for (std::uint8_t octant = 0; octant < 8; octant++)
				set(std::make_unique<Branch>(this, octant, color));
	}
	void Branch::write(std::ostream& out) const {
		if (!parent && !first()) {// Empty model case
			char branchHeaders[15] = {};
			out.write(branchHeaders, sizeof branchHeaders);
			out.put(LEAF_2BYTE);//2-byte payload leaf header
			out.put(0);//Both foreground and background zero
			out.put(0);
			return;
		}
		std::uint8_t collapsedValue = tryCollapse();
		if (collapsedValue != 0) {
			out.put(BRANCH_COLLAPSED | (octant & 0b111));//Header
			out.put(collapsedValue);
			return;
		}
		out.put(BRANCH_REGULAR | ((count() - 1) << 3) | (octant & 0b111));//Header
		for (std::uint8_t i = 0; i < 8; i++)
			if (children[i])
				children[i]->write(out);
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
	Branch& Branch::operator=(Branch&& other) noexcept {
		if (this != &other) {
			octant = other.octant;
			parent = other.parent;
			children = std::move(other.children);
		}
		return *this;
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
	std::uint8_t Branch::tryCollapse() const {
		return tryCollapsing(tryCollapseGetColor());
	}
	std::uint8_t Branch::tryCollapsing(std::uint8_t color) const {
		if (color == 0)
			return 0;
		for (const std::unique_ptr<Node>& child : children) {
			if (!child)
				return 0;
			Leaf* leaf = dynamic_cast<Leaf*>(child.get());
			if (leaf) {
				for (std::uint8_t i = 0; i < 8; i++)
					if (leaf->operator[](i) != color)
						return 0;
			}
			else {
				Branch* branch = dynamic_cast<Branch*>(child.get());
				if (branch && branch->tryCollapsing(color) == 0)
					return 0;
			}
		}
		return color;
	}
	std::uint8_t Branch::tryCollapseGetColor() const {
		if (!children[0])
			return 0;
		Leaf* leaf = dynamic_cast<Leaf*>(children[0].get());
		if (leaf)
			return leaf->operator[](0);
		Branch* branch = dynamic_cast<Branch*>(children[0].get());
		if (branch)
			return branch->tryCollapseGetColor();
		return 0;
	}
}
