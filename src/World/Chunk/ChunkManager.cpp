#include "ChunkManager.h"

#include "World/World.h"
#include "Utils/Mutexes.h"

#include <chrono>
#include <iostream>

#include "Utils/UtilityFunctions.h"

ChunkManager::ChunkManager(World* world) :
	world(world),
	generator(world->getSeed(), world)
{ }

ChunkManager::~ChunkManager() {

	for (auto& c : chunks)
		saveChunk(c.second);
}

Chunk* ChunkManager::getChunk(int x, int z) {

	Vector2 pos{ x, z };

	if (!chunkExistsAt(x, z)) {
		MUTEX(Mutexes::get().blockMutex,
			chunks.emplace(pos, std::move(Chunk(world, { x, z })));
		);
	}

	MUTEX(Mutexes::get().blockMutex,
		Chunk* chunk = &chunks[pos];
	);
	return chunk;
}

bool ChunkManager::makeMesh(int x, int z) {
	
	Chunk* chunk = getChunk(x, z);

	if (chunk->isMeshMade() || chunk->isUpdating())
		return false;

	for (int ox = -1; ox <= 1; ox++)
		for (int oz = -1; oz <= 1; oz++)
			getChunk(x + ox, z + oz)->load(generator);

	chunk->LoadLights();
	chunk->FinishLights();
	return chunk->makeMeshes();
}

bool ChunkManager::chunkExistsAt(int x, int z) {
	MUTEX(Mutexes::get().blockMutex,
		bool found = chunks.find({ x, z }) != chunks.end();
	);
	return found;
}

bool ChunkManager::chunkLoadedAt(int x, int z) {
	
	if (chunkExistsAt(x, z)) {
		MUTEX(Mutexes::get().blockMutex,
			bool loaded = chunks.find({ x, z })->second.isLoaded();
		);
		return loaded;
	}

	return false;
}

void ChunkManager::unloadChunkAt(int x, int z) {
	
	if (chunkExistsAt(x, z)) {
		auto it = chunks.find({ x, z });
		unloadChunkAt(it);
	}
}

void ChunkManager::unloadChunkAt(std::unordered_map<Vector2, Chunk>::iterator & it) {

	MUTEX(Mutexes::get().blockMutex,
		saveChunk(it->second);
		it = chunks.erase(it);
	);	
}

void ChunkManager::saveChunk(Chunk & c) {

	c.save();
}

std::unordered_map<Vector2, Chunk>& ChunkManager::getChunks() {
	return chunks;
}

TerrainGenerator & ChunkManager::getTerrainGenerator() {
	return generator;
}
