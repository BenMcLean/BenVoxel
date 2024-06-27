#include "BenVoxel.h"

int main()
{
	std::ifstream inFile;
	inFile.open("SORA.BEN", std::ios::binary);
	BenVoxel::SparseVoxelOctree svo = BenVoxel::SparseVoxelOctree(inFile);
	inFile.close();
	std::ofstream outFile;
	outFile.open("SORA2.BEN", std::ios::binary);
	svo.write(outFile);
	outFile.close();
	return 0;
}
