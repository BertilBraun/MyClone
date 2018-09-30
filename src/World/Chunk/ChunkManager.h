#pragma once

#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"

#include "Renderer/MasterRenderer.h"
#include "Math/Vector2.h"

#include "World/Building/TerrainGenerator.h"

#include "Chunk.h"

class ChunkManager {
public:
	ChunkManager(World* world);
	~ChunkManager();

	Chunk* getChunk(int x, int z);

	bool makeMesh(int x, int z);

	bool chunkExistsAt(int x, int z);
	bool chunkLoadedAt(int x, int z);

	void unloadChunkAt(int x, int z);
	void unloadChunkAt(std::unordered_map<Vector2, Chunk>::iterator& it);

	void saveChunk(Chunk& c);

	std::unordered_map<Vector2, Chunk>& getChunks();

	TerrainGenerator& getTerrainGenerator();

private:
	std::unordered_map<Vector2, Chunk> chunks;
	TerrainGenerator generator;
	World* world;
};