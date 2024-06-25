#pragma once
#include <iostream>
#include <array>
#include "Node.h"
#include "Leaf.h"
namespace BenVoxel {
	class Branch : public Node {
	protected:
		std::array<Node*, 8> children = {};
	public:
		Branch(Node* parent, std::uint8_t header, std::array<Node*, 8>& children);
		Branch(Node* parent, std::istream& in);
		void write(std::ostream& out) const override;
		std::uint8_t childCount() const;
		Node* getChild(std::uint8_t child) const;
		Node* setChild(Node* child);
		Node* removeChild(std::uint8_t child);
	};
}
