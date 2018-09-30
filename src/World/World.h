#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

#include "glm/glm.hpp"

#include "Chunk/ChunkManager.h"
#include "Entity/Player.h"
#include "Events/WorldEvent.h"

class World {
public:
	World(Player* player, Camera* camera, WorldInfo info);
	~World();

	Chunk* getChunk(int x, int z);

	ChunkBlock	getBlock(int x, int y, int z);
	void		setBlock(int x, int y, int z, ID ID);

	GLuint		getHeight(int x, int z);
	Biome::Biome& getBiome(int x, int z);

	int	 getSunlight(int x, int y, int z);
	void setSunlight(int x, int y, int z, int val);

	int	 getTorchlight(int x, int y, int z);
	void setTorchlight(int x, int y, int z, int val);

	void resetSunlight(int x, int y, int z);
	void resetTorchlight(int x, int y, int z);

	void UpdateChunk(int x, int y, int z);

	void Update(float deltaTime);
	void UpdateEvents(float deltaTime);

	void LoadChunk(int x, int z);
	void saveAll();

	void Render(MasterRenderer& renderer);

	void addChunkSectionToUpdate(ChunkSection* cs);
	
	template<typename T, typename... Args>
	void pushEvent(Args&&... args) {
		events.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	
	Player* getPlayer();
	glm::vec3 getSpawnPoint();
	void setSpawnPointSet(bool v);
	int getSeed();
	WorldInfo& getWorldInfo();

private:
	inline void loadChunks(Camera* camera);
	inline void UpdateChunks();
	
	ChunkManager manager;
	WorldInfo worldInfo;
	Player* player;
	Camera* camera;
	std::vector<std::unique_ptr<WorldEvent>> events;
	std::vector<ChunkSection*> updateChunkSections;
	std::vector<Chunk*> deleteChunks;

	//WORLD LOADING STUFF
	std::atomic<bool> running = true;
	std::atomic<bool> updating = false;
	std::vector<std::thread> chunkLoadingThreads;
	int loadDistance = 2;
	bool stopChecking = false;
	bool spawnPointSet = false;
	Vector2 camCoords;

};
