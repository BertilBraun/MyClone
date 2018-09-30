#include "World.h"

#include "SFML/Graphics.hpp"

#include "Chunk/Chunk.h"
#include "Utils/UtilityFunctions.h"

#include "Events/BlockBreakEvent.h"
#include "Events/BlockPlaceEvent.h"
#include "Math/Ray.h"
#include "Utils/Mutexes.h"

#include "defines.h"

#include "Utils/ToggleKey.h"
#include "Utils/Random.h"

World::World(Player* player, Camera* camera, WorldInfo info) :
	manager(this),	
	player(player),	
	camera(camera),
	worldInfo(info)
{
	camCoords = chunkCoord(camera->getPos().x, camera->getPos().z);
	Mutexes::get().mutex.lock();

	chunkLoadingThreads.emplace_back([&] {

		MUTEX(Mutexes::get().mutex, );

		while (running)
			UpdateChunks();
	});

	for (int i = 0; i < 4; i++)
		chunkLoadingThreads.emplace_back([&] {

			MUTEX(Mutexes::get().mutex, );

			while (running)
				loadChunks(this->camera);
			
		});
}

World::~World() {
	running = false;

	for (auto& t : chunkLoadingThreads)
		t.join();
}

inline void World::loadChunks(Camera * camera) {

		std::this_thread::sleep_for(std::chrono::duration<float>(0.005));

		if (stopChecking || !spawnPointSet || updating)
			return;

		bool isMeshMade = false;
		Vector2 cam = chunkCoord(camera->getPos().x, camera->getPos().z);

		for (int i = 0; i < loadDistance; i++)
			for (int x = cam.x - i; x <= cam.x + i; x++)
				for (int z = cam.z - i; z <= cam.z + i; z++) {
					MUTEX(Mutexes::get().mutex,
						isMeshMade = manager.makeMesh(x, z);
					);

					if (isMeshMade || updating || !running)
						return;
				}

		if (!isMeshMade)
			loadDistance++;

		if (loadDistance >= Config::get().renderDistance) {
			loadDistance = 2;
			stopChecking = true;
		}
	
}

inline void World::UpdateChunks() {

	std::this_thread::sleep_for(std::chrono::duration<float>(0.005));

	if (!deleteChunks.size() && !updateChunkSections.size())
		return;

	MUTEX(Mutexes::get().updateMutex,

		for (ChunkSection* cs : updateChunkSections) {
			getChunk(cs->getPos().x, cs->getPos().z)->FinishLights();
			cs->buildMesh();
		}
	updateChunkSections.clear();

	updating = false;

	for (Chunk* chunk : deleteChunks)
		manager.unloadChunkAt(chunk->getPos().x, chunk->getPos().y);
	deleteChunks.clear();
	);

	/*if (!deleteChunks.size())
		continue;

	MUTEX(Mutexes::get().updateMutex,

		if (deleteChunks.size()) {
			for (Chunk* chunk : deleteChunks)
				manager.unloadChunkAt(chunk->getPos().x, chunk->getPos().y);
			deleteChunks.clear();
		}
	);*/
}

Chunk* World::getChunk(int x, int z) {
	TRY(return manager.getChunk(x, z))
}

ChunkBlock World::getBlock(int x, int y, int z) {
	TRY(
		if (y < 0 || y >= CHUNK_AREA)
			return ID::Air;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		if (!manager.chunkLoadedAt(c.x, c.z))
			return ID::Air;

		return getChunk(c.x, c.z)->getBlock(b.x, y, b.z);
	)
}

void World::setBlock(int x, int y, int z, ID ID) {
	TRY(
		if (y < 0 || y >= CHUNK_AREA)
			return;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		getChunk(c.x, c.z)->setBlock(b.x, y, b.z, ID);
	)
}

int World::getSunlight(int x, int y, int z) {
	TRY(
		if (y < 0 || y >= CHUNK_AREA)
			return 0;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		return getChunk(c.x, c.z)->getSunlight(b.x, y, b.z);
	)
}

void World::setSunlight(int x, int y, int z, int val) {
	TRY(	
		if (y < 0 || y >= CHUNK_AREA || val <= 0)
			return;
	
		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		getChunk(c.x, c.z)->setSunlight(b.x, y, b.z, std::min(val, LIGHT_MAX));
	)
}

GLuint World::getHeight(int x, int z) {
	TRY(
		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		if (!manager.chunkLoadedAt(c.x, c.z))
			return 0;

		return getChunk(c.x, c.z)->getHeight(b.x, b.z);
	)
}

Biome::Biome & World::getBiome(int x, int z) {
	Vector2 c = chunkCoord(x, z);
	Vector2 b = blockCoord(x, z);

	return manager.getTerrainGenerator().getBiome(b.x, b.z, c.x, c.z);
}

int World::getTorchlight(int x, int y, int z) {

	if (y < 0 || y >= CHUNK_AREA)
		return 0;

	Vector2 c = chunkCoord(x, z);
	Vector2 b = blockCoord(x, z);

	return getChunk(c.x, c.z)->getTorchlight(b.x, y, b.z);
}

void World::resetSunlight(int x, int y, int z) {
	TRY(
		if (y < 0 || y >= CHUNK_AREA)
			return;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		getChunk(c.x, c.z)->resetSunlight(b.x, y, b.z);
	)
}

void World::resetTorchlight(int x, int y, int z) {
	TRY(
		if (y < 0 || y >= CHUNK_AREA)
			return;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		getChunk(c.x, c.z)->resetTorchlight(b.x, y, b.z);
	)
}

void World::setTorchlight(int x, int y, int z, int val) {
	TRY(
		if (y < 0 || y >= CHUNK_AREA || val <= 0)
			return;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		getChunk(c.x, c.z)->setTorchlight(b.x, y, b.z, std::min(val, LIGHT_MAX));
	)
}

void World::UpdateChunk(int x, int y, int z) {
	TRY(
		int by = y % CHUNK_SIZE;

		Vector2 c = chunkCoord(x, z);
		Vector2 b = blockCoord(x, z);

		MUTEX(Mutexes::get().updateMutex,

			addChunkSectionToUpdate(getChunk(c.x, c.z)->getChunkSection(y));

			if (b.x == 0)
				addChunkSectionToUpdate(getChunk(c.x - 1, c.z)->getChunkSection(y));
			else if (b.x == CHUNK_SIZE - 1)
				addChunkSectionToUpdate(getChunk(c.x + 1, c.z)->getChunkSection(y));

			if (by == 0)
				addChunkSectionToUpdate(getChunk(c.x, c.z)->getChunkSection(y - 1));
			else if (by == CHUNK_SIZE - 1)
				addChunkSectionToUpdate(getChunk(c.x, c.z)->getChunkSection(y + 1));

			if (b.z == 0)
				addChunkSectionToUpdate(getChunk(c.x, c.z - 1)->getChunkSection(y));
			else if (b.z == CHUNK_SIZE - 1)
				addChunkSectionToUpdate(getChunk(c.x, c.z + 1)->getChunkSection(y));
		);
	)
}

void World::Update(float deltaTime) {
	
	UpdateEvents(deltaTime);

	/*if (!updateChunkSections.size())
		return;

	MUTEX(Mutexes::get().updateMutex,

		for (ChunkSection* cs : updateChunkSections) {
			getChunk(cs->getPos().x, cs->getPos().z)->FinishLights();
			cs->buildMesh();
		}
		updateChunkSections.clear();

		updating = false;
	);*/	
}

void World::UpdateEvents(float deltaTime) {
	static ToggleButton right(sf::Mouse::Button::Right, 0.2f);

	bool breakEvent = true;

	for (auto& e : events)
		switch (e->getEventType()) {
		case EventType::BREAK:
			breakEvent = false;
			break;
		}

	if (breakEvent && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		pushEvent<BlockBreakEvent>(this, camera, player);

	if (right.isButtonPressed())
		pushEvent<BlockPlaceEvent>(this, camera, player);

	for (auto it = events.begin(); it != events.end(); )
		it = (*it)->Update(deltaTime) ? events.erase(it) : it + 1;
}

void World::LoadChunk(int x, int z) {
	manager.getChunk(x, z)->load(manager.getTerrainGenerator());
}

void World::saveAll() {
	worldInfo.Save(*player);

	MUTEX(Mutexes::get().updateMutex,

		for (auto& chunk : manager.getChunks()) {
			if (chunk.second.isDeleted())
				continue;
			else
				chunk.second.save();
		}
	);
}

void World::Render(MasterRenderer& renderer) {

	Vector2 cam = chunkCoord(camera->getPos().x, camera->getPos().z);

	if (cam != camCoords) {
		stopChecking = false;
		camCoords = cam;
	}

	int renderDistance = Config::get().renderDistance;

	int minX = (cam.x) - renderDistance,
		minZ = (cam.z) - renderDistance,
		maxX = (cam.x) + renderDistance,
		maxZ = (cam.z) + renderDistance;

	Mutexes::get().updateMutex.lock(); //MUTEX(Mutexes::get().updateMutex,

		for (auto& chunk : manager.getChunks()) {

			glm::ivec2 pos = chunk.second.getPos();

			if (chunk.second.isDeleted())
				continue;

			if (minX > pos.x || minZ > pos.y || maxZ < pos.y || maxX < pos.x) {
				chunk.second.setDeleted(true);
				deleteChunks.push_back(&chunk.second);
			}
			else if (camera->isBoxInFrustum(chunk.second.getAABB()))
				chunk.second.Render(renderer, camera);		
		}
	Mutexes::get().updateMutex.unlock(); //);

	for (auto& e : events)
		e->Display(renderer);	
}

void World::addChunkSectionToUpdate(ChunkSection* cs) {
	TRY(
		updating = true;
		cs->setUpdating(true);
		updateChunkSections.emplace_back(cs);
	)
}

Player* World::getPlayer() {
	return player;
}

glm::vec3 World::getSpawnPoint() {
	
	glm::vec3 point;
	int attempts = 0;
	spawnPointSet = false;

	do
	{
		attempts++;

		Vector2 c = {	Rand::get().intInRange(20, 40),
						Rand::get().intInRange(20, 40) };

		Vector2 b = {	Rand::get().intInRange(1, CHUNK_SIZE - 2),
						Rand::get().intInRange(1, CHUNK_SIZE - 2) };

		LoadChunk(c.x, c.z);

		point = glm::vec3(	c.x * CHUNK_SIZE + b.x,
							getChunk(c.x, c.z)->getHeight(b.x, b.z) + 2.6f,
							c.z * CHUNK_SIZE + b.z);

		if (point.y < WATERLEVEL)
			point.y = 0;

	} while (player->collision(this, point));
	
	std::cout << "Spawnfinding took : " << attempts << " trys\n\n";
	spawnPointSet = true;

	return point;	
}

void World::setSpawnPointSet(bool v) {
	spawnPointSet = v;
}

int World::getSeed() {
	return worldInfo.seed;
}

WorldInfo& World::getWorldInfo() {
	return worldInfo;
}
