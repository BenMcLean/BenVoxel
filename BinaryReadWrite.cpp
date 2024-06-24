#include "BinaryReadWrite.h"
void BenVoxel::BinaryReadWrite::writeU64(std::ostream& out, std::uint64_t x) {
	char bytes[8];
	uint64_to_le(x, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
void BenVoxel::BinaryReadWrite::writeU32(std::ostream& out, std::uint32_t x) {
	char bytes[4];
	uint32_to_le(x, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
void BenVoxel::BinaryReadWrite::writeU16(std::ostream& out, std::uint16_t x) {
	char bytes[2];
	uint16_to_le(x, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
void BenVoxel::BinaryReadWrite::write64(std::ostream& out, std::int64_t x) {
	char bytes[8];
	uint64_to_le(x, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
void BenVoxel::BinaryReadWrite::write32(std::ostream& out, std::int32_t x) {
	char bytes[4];
	uint32_to_le(x, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
void BenVoxel::BinaryReadWrite::write16(std::ostream& out, std::int16_t x) {
	char bytes[2];
	uint16_to_le(x, bytes);
	if (!out.write(bytes, sizeof bytes)) {
		throw std::runtime_error("Error writing");
	}
}
std::uint64_t BenVoxel::BinaryReadWrite::readU64(std::istream& in) {
	char bytes[8];
	if (!in.read(bytes, sizeof bytes)) {
		throw std::runtime_error("Error reading");
	}
	return le_to_uint64(bytes);
}
std::uint32_t BenVoxel::BinaryReadWrite::readU32(std::istream& in) {
	char bytes[4];
	if (!in.read(bytes, sizeof bytes)) {
		throw std::runtime_error("Error reading");
	}
	return le_to_uint32(bytes);
}
std::uint16_t BenVoxel::BinaryReadWrite::readU16(std::istream& in) {
	char bytes[2];
	if (!in.read(bytes, sizeof bytes)) {
		throw std::runtime_error("Error reading");
	}
	return le_to_uint16(bytes);
}
std::int64_t BenVoxel::BinaryReadWrite::read64(std::istream& in) {
	char bytes[8];
	if (!in.read(bytes, sizeof bytes)) {
		throw std::runtime_error("Error reading");
	}
	return le_to_int64(bytes);
}
std::int32_t BenVoxel::BinaryReadWrite::read32(std::istream& in) {
	char bytes[4];
	if (!in.read(bytes, sizeof bytes)) {
		throw std::runtime_error("Error reading");
	}
	return le_to_int32(bytes);
}
std::int16_t BenVoxel::BinaryReadWrite::read16(std::istream& in) {
	char bytes[2];
	if (!in.read(bytes, sizeof bytes)) {
		throw std::runtime_error("Error reading");
	}
	return le_to_int16(bytes);
}
