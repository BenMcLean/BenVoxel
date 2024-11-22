#pragma once
#include <iostream>
#include <array>
#include "Node.h"
#include "Leaf.h"
namespace BenVoxel {
	class Branch : public Node {
	protected:
		std::array<std::unique_ptr<Node>, 8> children;
	public:
		Branch();
		Branch(Branch* parent, std::uint8_t octant);
		Branch(Branch* parent, std::uint8_t octant, std::uint8_t color);
		Branch(Branch* parent, std::istream& in);
		virtual ~Branch() override = default;
		void write(std::ostream& out) const override;
		std::uint8_t count() const;
		Node* first() const;
		Node* nextValidChild(std::uint8_t previous) const;
		Node* operator[](std::uint8_t octant) const;
		Branch& operator=(Branch&& other) noexcept;
		void set(std::unique_ptr<Node> child);
		void remove(std::uint8_t octant);
		void expandCollapsed(std::uint8_t color);
		std::uint8_t tryCollapse() const;
		std::uint8_t tryCollapsing(std::uint8_t color) const;
		std::uint8_t tryCollapseGetColor() const;
	};
}
