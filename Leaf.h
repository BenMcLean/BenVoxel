#include <iostream>
#include "Node.h"
using namespace std;
class Leaf : public Node {
private:
	void _init(Node* parent, uint8_t header, uint64_t data);
public:
	uint64_t data;
	Leaf(Node* parent, uint8_t header, uint64_t data);
	Leaf(Node* parent, istream in);
	void write(ostream out) const;
};
