#include <iostream>
#include "Node.h"
#include "BinaryReadWrite.h"
class Leaf : public Node {
public:
	std::uint64_t data;
	Leaf(Node* parent, std::uint8_t header, std::uint64_t data);
	Leaf(Node* parent, std::istream& in);
	void write(std::ostream& out) const;
};
