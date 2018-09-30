#pragma once

#include "World/Chunk/Chunk.h"
#include "Math/NoiseGenerator.h"

#include <string>

namespace Biome {

	class Biome {
	public:
		Biome(int seed, int treeFreq, int plantFreq);
		~Biome();

		int getHeight(int x, int z, int cx, int cz);

		virtual void addTree(int x, int y, int z, Chunk* c);

		virtual ChunkBlock getBeachBlock() = 0;
		virtual ChunkBlock getUnderwaterBlock() = 0;
		virtual ChunkBlock getUnderEarth() = 0;
		virtual ChunkBlock getTopBlock() = 0;
		virtual ChunkBlock getPlant() = 0;

		int getTreeFreq();
		int getPlantFreq();

		std::string name = "NONAME";
	protected:
		NoiseGenerator noise;
		int treeFreq, plantFreq;
	};
}