#include <iostream>
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
	};
}
