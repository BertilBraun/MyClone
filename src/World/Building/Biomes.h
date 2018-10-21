#pragma once

#include "Biome.h"

namespace Biome {

	class Desert : public Biome {
	public:
		Desert(int seed);

		ChunkBlock getBeachBlock()		override;
		ChunkBlock getUnderwaterBlock() override;
		ChunkBlock getUnderEarth()		override;
		ChunkBlock getTopBlock()		override;
		ChunkBlock getPlant()			override;

		void addTree(int x, int y, int z, Chunk* c) override;

	};

	class Grass : public Biome {
	public:
		Grass(int seed);

		ChunkBlock getBeachBlock()		override;
		ChunkBlock getUnderwaterBlock() override;
		ChunkBlock getUnderEarth()		override;
		ChunkBlock getTopBlock()		override;
		ChunkBlock getPlant()			override;
	};

	class Forest : public Biome {
	public:
		Forest(int seed);

		ChunkBlock getBeachBlock()		override;
		ChunkBlock getUnderwaterBlock() override;
		ChunkBlock getUnderEarth()		override;
		ChunkBlock getTopBlock()		override;
		ChunkBlock getPlant()			override;
	};

	class SnowForest : public Biome {
	public:
		SnowForest(int seed);

		ChunkBlock getBeachBlock()		override;
		ChunkBlock getUnderwaterBlock() override;
		ChunkBlock getUnderEarth()		override;
		ChunkBlock getTopBlock()		override;
		ChunkBlock getPlant()			override;

		void addTree(int x, int y, int z, Chunk* c) override;
	};

	class HighLands : public Biome {
	public:
		HighLands(int seed);

		ChunkBlock getBeachBlock()		override;
		ChunkBlock getUnderwaterBlock() override;
		ChunkBlock getUnderEarth()		override;
		ChunkBlock getTopBlock()		override;
		ChunkBlock getPlant()			override;

		void addTree(int x, int y, int z, Chunk* c) override;
	};
}