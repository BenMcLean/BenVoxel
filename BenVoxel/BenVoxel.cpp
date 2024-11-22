#include "BenVoxel.h"
/*
namespace {
	static void printVoxels(std::list<BenVoxel::Voxel> voxels) {
		for (BenVoxel::Voxel voxel : voxels)
			std::cout
			<< "X: " << voxel.x << ", "
			<< "Y: " << voxel.y << ", "
			<< "Z: " << voxel.z << ", "
			<< "Index: " << static_cast<uint16_t>(voxel.index)
			<< std::endl;
	}
}
*/
int main()
{
	std::ifstream inFile;
	inFile.open("./SORA.SVO", std::ios::binary);
	BenVoxel::SparseVoxelOctree svo(inFile);
	inFile.close();
	std::ofstream outFile;
	outFile.open("./SORA2.SVO", std::ios::binary);
	svo.write(outFile);
	outFile.close();

	//BenVoxel::SparseVoxelOctree svo;
	//svo.set(1, 1, 1, 1);
	//printVoxels(svo.voxels());
	//std::ofstream outFile;
	//outFile.open("OUT.BEN", std::ios::binary);
	//svo.write(outFile);
	//outFile.close();
	return 0;
}
