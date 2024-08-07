#pragma once
#include <iostream>
#include <stack>
namespace BenVoxel {
	class Branch;
	const struct Position {
	public:
		const std::uint16_t x;
		const std::uint16_t y;
		const std::uint16_t z;
		Position(std::uint16_t x, std::uint16_t y, std::uint16_t z);
	};
	class Node {
	protected:
		std::uint8_t octant = 0;
		Branch* parent = nullptr;//Not owned, nullptr indicates root Branch
	public:
		Node(Branch* parent, std::uint8_t header);
		Node(Branch* parent, std::istream& in);
		virtual ~Node() = default;
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		virtual void write(std::ostream& out) const = 0;
		std::uint8_t getOctant() const;
		Branch* getParent() const;
		Position position() const;
	};
}
