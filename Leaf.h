#include <iostream>
#include "Node.h"
class Leaf : public Node {
private:
	void _init(Node* parent, std::uint8_t header, std::uint64_t data);
public:
	std::uint64_t data;
	Leaf(Node* parent, std::uint8_t header, std::uint64_t data);
	Leaf(Node* parent, std::istream& in);
	void write(std::ostream& out) const;
};
