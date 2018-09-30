#pragma once

#include "World/Chunk/Chunk.h"

#include "Biomes.h"

class World;

class TerrainGenerator {
public:
	TerrainGenerator(int seed, World* world);
	~TerrainGenerator();

	void LoadChunk(Chunk* c);


	Biome::Biome & getBiome(int x, int z, int cx, int cz);
private:
	bool tryLoadFromFile();

	Chunk * c = nullptr;
	World * world = nullptr;

	Biome::Desert		desert;
	Biome::Forest		forest;
	Biome::SnowForest	snowForest;
	Biome::HighLands	highLands;
	Biome::Grass		grass;

	NoiseGenerator biomeNoise;
};

