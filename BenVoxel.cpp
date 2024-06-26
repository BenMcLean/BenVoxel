#include "BenVoxel.h"

int main()
{
	std::ifstream inFile;
	inFile >> std::noskipws;
	inFile.open("EMPTY.BEN", std::ios::binary);
	BenVoxel::SparseVoxelOctree svo = BenVoxel::SparseVoxelOctree(inFile);
	inFile.close();
	std::ofstream outFile;
	outFile << std::noskipws;
	outFile.open("EMPTY2.BEN", std::ios::binary);
	svo.write(outFile);
	outFile.close();
	return 0;
}
