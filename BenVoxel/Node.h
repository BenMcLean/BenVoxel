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
		static const std::uint8_t BRANCH_REGULAR = 0b00000000,
			BRANCH_COLLAPSED = 0b01000000,
			LEAF_2BYTE = 0b10000000,
			LEAF_8BYTE = 0b11000000,
			TYPE_MASK = 0b11000000;
	public:
		Node(Branch* parent, std::uint8_t header);
		Node(Branch* parent, std::istream& in);
		virtual ~Node() = default;
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		virtual void write(std::ostream& out) const = 0;
		std::uint8_t getOctant() const;
		Branch* getParent() const;
		std::uint8_t depth() const;
		Position position() const;
		static std::uint8_t readByte(std::istream& in, const char* errorMessage = "Failed to read byte from input stream.");
		static std::uint8_t peekByte(std::istream& in, const char* errorMessage = "Failed to peek at byte from input stream.");
	};
}
