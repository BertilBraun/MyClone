#include "TerrainGenerator.h"

#include "Utils/Random.h"
#include "World/World.h"
#include <fstream>

#include "Math/PerlinNoise.h"


TerrainGenerator::TerrainGenerator(int seed, World* world) :
	desert(seed),
	forest(seed),
	snowForest(seed),
	highLands(seed),
	grass(seed),
	biomeNoise(434895), //world->getWorldInfo().seed * 
	world(world)
{

	NoiseParameters biomeParmams;
	biomeParmams.octaves = 5;
	biomeParmams.amplitude = 120;
	biomeParmams.smoothness = 1035;
	biomeParmams.heightOffset = 0;
	biomeParmams.roughness = 0.75;

	biomeNoise.setParameters(biomeParmams);
}


TerrainGenerator::~TerrainGenerator()
{
}

void TerrainGenerator::LoadChunk(Chunk * c) {
	this->c = c;

	try {
		sf::Clock clock;

		int cx = c->getPos().x,
			cz = c->getPos().y;

		if (tryLoadFromFile()) {
			//std::cout << clock.restart().asMilliseconds() << " ms to load from File\n\n";
			return;
		}

		for (int x = 0; x < CHUNK_SIZE; x++)
			for (int z = 0; z < CHUNK_SIZE; z++) {

				Biome::Biome& biome = getBiome(x, z, cx, cz);

				int h = (int)biome.getHeight(x, z, cx, cz);

				if (h > WATERLEVEL + 2)
					if (!Rand::get().intInRange(0, biome.getTreeFreq()))
						biome.addTree(x, h, z, c);
					else if (!Rand::get().intInRange(0, biome.getPlantFreq()))
						c->setBlock(x, h + 1, z, biome.getPlant().id);

				for (int y = 0; y <= h || y <= WATERLEVEL; y++) {

					if (h <= WATERLEVEL) {

						if (y > h)
							c->setBlock(x, y, z, ID::Water);

						else if (y == h && y == WATERLEVEL)
							c->setBlock(x, y, z, biome.getBeachBlock().id);

						else if (y == h)
							c->setBlock(x, y, z, biome.getUnderwaterBlock().id);

						else
							c->setBlock(x, y, z, biome.getUnderEarth().id);
					}
					else {

						if (y > WATERLEVEL && y < WATERLEVEL + 3)
							c->setBlock(x, y, z, biome.getBeachBlock().id);

						else {
							if (y == h)
								c->setBlock(x, y, z, biome.getTopBlock().id);

							else if (y > h - 3)
								c->setBlock(x, y, z, ID::Dirt);

							else
								c->setBlock(x, y, z, biome.getUnderEarth().id);
						}
					}
				}
			}

	}
	catch (std::exception& e) {
		throw e;
	}
	//std::cout << clock.restart().asMilliseconds() << " ms to load\n\n";
	c = nullptr;
}

bool TerrainGenerator::tryLoadFromFile() {

	int cx = c->getPos().x,
		cz = c->getPos().y;

	std::string path("res/saves/" + world->getWorldInfo().path + "/chunks/" + std::to_string(cx) + "  " + std::to_string(cz) + ".chunk");

	std::ifstream stream(path);

	if (!stream.is_open()) 
		return false;

	int size = 0,
		id = 0;

	stream >> size;

	for (int i = 0; i < size; i++)
		for (int x = 0; x < CHUNK_SIZE; x++)
			for (int y = 0; y < CHUNK_SIZE; y++)
				for (int z = 0; z < CHUNK_SIZE; z++) {
					stream >> id;
					c->setBlock(x, i * CHUNK_SIZE + y, z, static_cast<ID>(id));
				}

	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
			if (c->getHeight(x, z))
				return true;
	
	return false;
}

Biome::Biome& TerrainGenerator::getBiome(int x, int z, int cx, int cz) {
	
	int h = (int)biomeNoise.getHeight(x, z, cx, cz);

	if (h > 160)
		return desert;

	else if (h > 150)
		return grass;

	else if (h > 135)
		return snowForest;

	else if (h > 120)
		return highLands;

	else if (h > 110)
		return forest;

	else if (h > 100)
		return grass;

	else
		return desert;
	
}
