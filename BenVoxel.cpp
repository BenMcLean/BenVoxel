#include "BenVoxel.h"

int main()
{
	std::ifstream inFile;
	inFile.open("EMPTY.BEN");
	BenVoxel::SparseVoxelOctree svo = BenVoxel::SparseVoxelOctree(inFile);
	inFile.close();
	std::ofstream outFile;
	outFile.open("EMPTY2.BEN");
	svo.write(outFile);
	outFile.close();
	return 0;
}
