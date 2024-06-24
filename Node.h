#include <iostream>
using namespace std;
class Node {
public:
	uint8_t header;
	Node* parent;
	Node(Node* parent, uint8_t header);
	Node(Node* parent, istream in);
	void write(ostream out) const;
};