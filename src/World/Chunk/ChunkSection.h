#pragma once

#include "Utils/Array3D.h"
#include "World/Blocks/ChunkBlock.h"

#include "defines.h"

#include "glm/glm.hpp"
#include "ChunkMesh.h"

#include "AABB/AABB.h"

class World;

class Layer {
public:
	void update(ChunkBlock cb);
	bool allSolid();

private:
	GLint anzSolids = 0;
};

class ChunkSection {
public:
	ChunkSection(World* world, const glm::ivec3& pos);
	~ChunkSection();

	ChunkBlock getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, ID id);

	void buildMesh();
	void bufferMesh();

	int	getSunlight(int x, int y, int z); 
	void setSunlight(int x, int y, int z, int val); 

	int	getTorchlight(int x, int y, int z); 
	void setTorchlight(int x, int y, int z, int val); 

	bool allSolid(int y);

	AABB& getAABB();

	bool isBuffered();
	bool isMeshMade();
	bool isUpdating();
	void setUpdating(bool v);

	ChunkMeshCollection& getMeshes();
	glm::ivec3& getPos();

private:
	std::array<Layer, CHUNK_SIZE> layers;
	Array3D<ChunkBlock, CHUNK_SIZE> blocks;
	glm::ivec3 pos; 
	World* world;
	AABB aabb;
	ChunkMeshCollection meshCollection;
	bool buffered = false, meshMade = false, updating = false;
};

