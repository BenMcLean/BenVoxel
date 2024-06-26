#pragma once
#include <iostream>
#include <array>
#include "Node.h"
#include "Leaf.h"
namespace BenVoxel {
	class Branch : public Node {
	protected:
		std::array<std::unique_ptr<Node>, 8> children = {};
	public:
		Branch(Branch* parent, std::uint8_t header);
		Branch(Branch* parent, std::istream& in);
		void write(std::ostream& out) const override;
		bool isLeaf() const override;
		std::uint8_t count() const;
		bool isEmpty() const;
		Node* operator[](std::uint8_t octant) const;
		void set(std::unique_ptr<Node> child);
		void remove(std::uint8_t octant);
	};
}
