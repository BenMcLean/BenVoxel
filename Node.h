#include <iostream>
class Node {
protected:
	void _init(Node* parent, std::uint8_t header);
public:
	std::uint8_t header;
	Node* parent;
	Node(Node* parent, std::uint8_t header);
	Node(Node* parent, std::istream& in);
	void write(std::ostream& out) const;
	std::uint8_t octant() const;
	bool isLeaf() const;
};
