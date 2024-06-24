#include <iostream>
#include "Node.h"
#include "BinaryReadWrite.h"
namespace BenVoxel {
	class Leaf : public Node {
	protected:
		std::uint8_t data[8];
	public:
		Leaf(Node* parent, std::uint8_t header, std::uint8_t(&data)[8]);
		Leaf(Node* parent, std::istream& in);
		void write(std::ostream& out) const override;
	};
}