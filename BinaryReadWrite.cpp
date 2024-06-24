#include "BinaryReadWrite.h"
void BinaryReadWrite::writeU64(std::ostream& out, std::uint64_t u64) {
	char bytes[8];
	uint64_to_le(u64, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
