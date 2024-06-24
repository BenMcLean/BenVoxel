#include <iostream>
#include "endian.hpp"
static class BinaryReadWrite {
public:
	static void writeU64(std::ostream& out, std::uint64_t u64);
};
