#include "Node.h"
#include "Branch.h"
namespace BenVoxel {
	Position::Position(std::uint16_t x, std::uint16_t y, std::uint16_t z) : x(x), y(y), z(z) { }
	Node::Node(Branch* parent, std::istream& in) {
		this->parent = parent;
		int header = in.peek();
		if (header < 0)
			throw std::runtime_error("Failed to read from input stream.");
		octant = header & 7;
	}
	Node::Node(Branch* parent, std::uint8_t header) {
		this->parent = parent;
		this->octant = header & 7;
	}
	std::uint8_t Node::getOctant() const {
		return octant;
	}
	Branch* Node::getParent() const {
		return const_cast<Branch*>(parent);
	}
	Position Node::position() const {
		std::stack<Node*> stack = {};
		Node* node = const_cast<Node*>(this);
		while (node) {
			stack.push(node);
			Branch* branch = node->parent;
			if (branch && !branch->isLeaf())
				node = (Node*)node->parent;
			else
				node = nullptr;
		}
		std::uint8_t count = 17 - stack.size();
		std::uint16_t x = 0, y = 0, z = 0;
		while (!stack.empty()) {
			node = stack.top();
			stack.pop();
			x = (x << 1) | node->getOctant() & 1;
			y = (y << 1) | (node->getOctant() >> 1) & 1;
			z = (z << 1) | (node->getOctant() >> 2) & 1;
		}
		x <<= count; y <<= count; z <<= count;
		return Position(x, y, z);
	}
}
