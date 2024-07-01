#include "BenVoxel.h"

int main()
{
	std::ifstream inFile;
	inFile.open("..\\..\\..\\SORA.BEN", std::ios::binary);
	BenVoxel::SparseVoxelOctree svo = BenVoxel::SparseVoxelOctree(inFile);
	inFile.close();
	std::ofstream outFile;
	outFile.open("SORA2.BEN", std::ios::binary);
	BenVoxel::SparseVoxelOctree(svo.voxels()).write(outFile);
	outFile.close();

	//BenVoxel::SparseVoxelOctree svo = {};
	//svo.set(1, 1, 1, 1);
	//std::ofstream outFile;
	//outFile.open("OUT.BEN", std::ios::binary);
	//svo.write(outFile);
	//outFile.close();
	return 0;
}
