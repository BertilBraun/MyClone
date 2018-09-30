#pragma once

#include "defines.h"
#include "ChunkSection.h"
#include "Utils/Array2D.h"
#include <queue>
#include <vector>

class World;
class MasterRenderer;
class Camera;
class TerrainGenerator;

class Chunk {
public:
	Chunk();
	Chunk(World* world, const glm::ivec2& pos);
	~Chunk();

	void load(TerrainGenerator& generator);

	ChunkSection* getChunkSection(int y);

	ChunkBlock	getBlock(int x, int y, int z);
	void		setBlock(int x, int y, int z, ID id);

	int	getSunlight(int x, int y, int z); 
	void setSunlight(int x, int y, int z, int val); 

	int	getTorchlight(int x, int y, int z);
	void setTorchlight(int x, int y, int z, int val); 

	void resetSunlight(int x, int y, int z);
	void resetTorchlight(int x, int y, int z);

	GLuint getHeight(int x, int z);
	GLuint getMaxHeight();

	void Render(MasterRenderer& renderer, Camera* camera);

	bool makeMeshes();
	void LoadLights();
	void FinishLights();
	void save();

	void setUpdating(bool d);
	bool isUpdating();
	void setDeleted(bool d);
	bool isDeleted();
	bool isLoaded();
	bool isMeshMade();
	glm::ivec2& getPos();
	AABB& getAABB();

private:
	bool outOfBound(int x, int z);

	std::queue<std::pair<glm::vec3, short>> sunRemovalQueue, torchRemovalQueue;
	std::queue<glm::vec3> sunLightQueue, torchLightQueue;

	std::vector<ChunkSection> sections;
	Array2D<GLuint, CHUNK_SIZE> heights;

	glm::ivec2 pos;
	World* world;
	AABB aabb;
	std::string	worldPath;
	bool loaded = false, hasMesh = false, deleted = false, updating = false;
};