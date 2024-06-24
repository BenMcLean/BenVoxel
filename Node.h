#include <iostream>
using namespace std;
class Node {
protected:
	void _init(Node* parent, uint8_t header);
public:
	uint8_t header;
	Node* parent;
	Node(Node* parent, uint8_t header);
	Node(Node* parent, istream in);
	void write(ostream out) const;
	uint8_t octant() const;
	bool isLeaf() const;
};
