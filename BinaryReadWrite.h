#pragma once
#include <iostream>
#include "endian.hpp"
namespace BenVoxel {
	static class BinaryReadWrite {
	public:
		static void writeU64(std::ostream& out, std::uint64_t x);
		static void writeU32(std::ostream& out, std::uint32_t x);
		static void writeU16(std::ostream& out, std::uint16_t x);
		static void write64(std::ostream& out, std::int64_t x);
		static void write32(std::ostream& out, std::int32_t x);
		static void write16(std::ostream& out, std::int16_t x);
		static std::uint64_t readU64(std::istream& in);
		static std::uint32_t readU32(std::istream& in);
		static std::uint16_t readU16(std::istream& in);
		static std::int64_t read64(std::istream& in);
		static std::int32_t read32(std::istream& in);
		static std::int16_t read16(std::istream& in);
	};
}
