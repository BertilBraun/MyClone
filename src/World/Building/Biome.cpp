#include "Biome.h"

#include "Utils/Random.h"

#include "Structures/StructureBuilder.h"

namespace Biome {

	Biome::Biome(int seed, int treeFreq, int plantFreq) :
		noise(seed),
		treeFreq(treeFreq),
		plantFreq(plantFreq)
	{ }


	Biome::~Biome()
	{
	}

	int Biome::getHeight(int x, int z, int cx, int cz) {

		return (int)noise.getHeight(x, z, cx, cz);
	}

	void Biome::addTree(int x, int y, int z, Chunk* c) {

		StructureBuilder builder(c);

		int ny = y + Rand::get().intInRange(4, 6);

		builder.addLayer(x - 2, z - 1, x + 2, z + 1, ny, ID::Leave);
		builder.addLayer(x - 2, z - 1, x + 2, z + 1, ny + 1, ID::Leave);

		builder.addLineX(x - 1, x + 1, ny, z + 2, ID::Leave);
		builder.addLineX(x - 1, x + 1, ny, z - 2, ID::Leave);

		builder.addLineX(x - 1, x + 1, ny + 1, z + 2, ID::Leave);
		builder.addLineX(x - 1, x + 1, ny + 1, z - 2, ID::Leave);

		builder.addLayer(x - 1, z - 1, x + 1, z + 1, ny + 2, ID::Leave);

		builder.addLineX(x - 1, x + 1, ny + 3, z, ID::Leave);
		builder.addLineZ(z - 1, z + 1, x, ny + 3, ID::Leave);

		builder.addLineY(y, ny + 2, x, z, ID::Wood);
	}

	int Biome::getTreeFreq() {
		return treeFreq;
	}

	int Biome::getPlantFreq() {
		return plantFreq;
	}
}