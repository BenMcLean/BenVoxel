#include "Leaf.h"
namespace BenVoxel {
	Leaf::Leaf(Branch* parent, std::uint8_t octant) : Node(parent, 0x80 | octant), data{} { }
	Leaf::Leaf(Branch* parent, std::istream& in) : Node(parent, in), data{} {
		std::uint8_t header = in.get();
		octant = header & 7;
		switch (header >> 6 & 3) {
		case 1: {
			std::uint8_t value = in.get();
			data.fill(value);
			break;
		}
		case 2: {
			std::uint8_t where = header >> 3 & 7,
				foreground = in.get(),
				background = in.get();
			for (int i = 0; i < 8; ++i)
				data[i] = i == where ? foreground : background;
			break;
		}
		default:
			in.read(reinterpret_cast<char*>(data.data()), 8);
			break;
		}
	}
	void Leaf::write(std::ostream& out) const {
		std::array<std::pair<std::uint8_t, std::uint8_t>, 8> occurrences; // Array to store pairs of (value, count) for each unique value in data
		std::uint8_t unique_count = 0;
		for (std::uint8_t value : data) {
			std::array<std::pair<std::uint8_t, std::uint8_t>, 8>::iterator it = std::find_if(
				occurrences.begin(), // Search for the current value in the occurrences array
				occurrences.begin() + unique_count, // Only search up to unique_count, as that's how many valid entries we have
				[value](const std::pair<std::uint8_t, std::uint8_t>& p) {
					return p.first == value;
				});
			if (it != occurrences.begin() + unique_count)
				it->second++; // Value found, increment its count
			else if (unique_count < 8) // Value not found and we haven't filled the array yet
				occurrences[unique_count++] = std::pair<std::uint8_t, std::uint8_t>{ value, 1 }; // Add new entry with count 1
			// If unique_count == 8 then we ignore any further unique values
		}
		std::sort( // Sort the occurrences array by count (second element of the pair)
			occurrences.begin(),
			occurrences.begin() + unique_count, // Only sort the portion of the array we've actually used (up to unique_count)
			[](const std::pair<std::uint8_t, std::uint8_t>& a, const std::pair<std::uint8_t, std::uint8_t>& b) {
				return a.second < b.second;
			});
		if (unique_count == 1) {
			out.put(0x40 | octant & 7); // Header
			out.put(occurrences[0].first);
		}
		else if (unique_count == 2 && occurrences[0].second == 1) {
			std::uint8_t index = static_cast<std::uint8_t>(std::distance(data.begin(),
				std::find(data.begin(), data.end(), occurrences[0].first)));
			out.put(0x80 | (index & 7) << 3 | octant & 7); // Header
			out.put(occurrences[0].first); // Foreground
			out.put(occurrences[1].first); // Background
		}
		else {
			out.put(0xC0 | octant & 7);
			out.write(reinterpret_cast<const char*>(data.data()), 8);
		}
	}
	std::uint8_t Leaf::operator[](std::uint8_t octant) const {
		return data[octant];
	}
	void Leaf::set(std::uint8_t octant, std::uint8_t index) {
		data[octant] = index;
		if (parent && data == std::array<std::uint8_t, 8>{})//This checks for all zeroes and modern compilers won't allocate a new array
			parent->remove(octant);
	}
}
