#include <iostream>
#include "Node.h"
#include "BinaryReadWrite.h"
namespace BenVoxel {
	class Branch : public Node {
	protected:
		Node* children[8];
	public:
		Branch(Node* parent, std::uint8_t header, Node* children[8]);
		//Branch(Node* parent, std::istream& in);
		void write(std::ostream& out) const override;
		std::uint8_t childCount() const;
		Node* getChild(std::uint8_t& child) const;
	};
}
