#include "Chunk.h"

#include "Renderer/MasterRenderer.h"
#include "Entity/Camera.h"
#include "World/World.h"

#include "Utils/UtilityFunctions.h"

#include "World/Building/TerrainGenerator.h"

#include <fstream>
#include <assert.h>

Chunk::Chunk() {
	__debugbreak();
}

Chunk::Chunk(World* world, const glm::ivec2& pos) :
	world(world),
	pos(pos),
	aabb(glm::vec3(CHUNK_SIZE, CHUNK_AREA, CHUNK_SIZE )), 
	worldPath(world->getWorldInfo().path),
	sections({	ChunkSection(world, glm::ivec3(pos.x, 0,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 1,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 2,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 3,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 4,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 5,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 6,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 7,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 8,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 9,  pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 10, pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 11, pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 12, pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 13, pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 14, pos.y)),
				ChunkSection(world, glm::ivec3(pos.x, 15, pos.y)) })
{
	aabb.UpdatePos(glm::vec3(pos.x * CHUNK_SIZE, 0, pos.y * CHUNK_SIZE));
	heights.fill(0);
}

Chunk::~Chunk() {
}

void Chunk::load(TerrainGenerator& generator) {

	if (loaded)
		return;

	generator.LoadChunk(this);
	loaded = true;
}

ChunkSection* Chunk::getChunkSection(int y) {

	if (y < 0 || y >= CHUNK_AREA)
		return nullptr;

	unsigned int index = y / CHUNK_SIZE;

	//while (index >= sections.size()) {
	//	TRY(
	//		sections.emplace_back(world, glm::ivec3(pos.x, sections.size(), pos.y));
	//	)
	//}

	return &sections[index];
}

bool Chunk::outOfBound(int x, int z) {
	return (
		x >= CHUNK_SIZE || z >= CHUNK_SIZE	||
		x < 0 || z < 0);
}

void Chunk::setBlock(int x, int y, int z, ID id) {

	if (y < 0 || y >= CHUNK_AREA)
		return;

	getChunkSection(y)->setBlock(x, y % CHUNK_SIZE, z, id);

	if (outOfBound(x, z))
		return;

	if (id == ID::Air)
		for (int i = heights.getIndex(x, z); i > 0; i--) {
			if (getBlock(x, i, z).id != ID::Air && getBlock(x, i, z).getData().blockType != BlockType::FLUID)
				return heights.setIndex(x, z, i);
		}
	else if (y > heights.getIndex(x, z))
		heights.setIndex(x, z, y);
	
}

ChunkBlock Chunk::getBlock(int x, int y, int z) {

	if (y < 0 || y >= CHUNK_AREA)
		return ID::Air;

	return getChunkSection(y)->getBlock(x, y % CHUNK_SIZE, z);
}

int Chunk::getSunlight(int x, int y, int z) {

	if (y < 0 || y >= CHUNK_AREA)
		return 0;

	return getChunkSection(y)->getSunlight(x, y % CHUNK_SIZE, z);
}

void Chunk::setSunlight(int x, int y, int z, int val) {

	if (y < 0 || y >= CHUNK_AREA)
		return;

	getChunkSection(y)->setSunlight(x, y % CHUNK_SIZE, z, val);
	sunLightQueue.emplace(pos.x * CHUNK_SIZE + x, y, pos.y * CHUNK_SIZE + z);
}

int Chunk::getTorchlight(int x, int y, int z) {

	if (y < 0 || y > CHUNK_AREA)
		return 0;

	return getChunkSection(y)->getTorchlight(x, y % CHUNK_SIZE, z);
}

void Chunk::setTorchlight(int x, int y, int z, int val) {

	if (y < 0 || y >= CHUNK_AREA)
		return;

	getChunkSection(y)->setTorchlight(x, y % CHUNK_SIZE, z, val);
	torchLightQueue.emplace(pos.x * CHUNK_SIZE + x, y, pos.y * CHUNK_SIZE + z);
}

void Chunk::resetSunlight(int x, int y, int z){ 

	int tx = x + pos.x * CHUNK_SIZE,
		tz = z + pos.y * CHUNK_SIZE;

	if (outOfChunkRange(x) || outOfChunkRange(z))
		world->resetSunlight(tx, y, tz);

	sunRemovalQueue.emplace(glm::vec3(tx, y, tz), getSunlight(x, y, z));
	getChunkSection(y)->setSunlight(x, y % CHUNK_SIZE, z, 0);
}

void Chunk::resetTorchlight(int x, int y, int z) {

	int tx = x + pos.x * CHUNK_SIZE,
		tz = z + pos.y * CHUNK_SIZE;

	if (outOfChunkRange(x) || outOfChunkRange(z))
		world->resetTorchlight(tx, y, tz);
	
	torchRemovalQueue.emplace(glm::vec3(tx, y, tz), getTorchlight(x, y, z));
	getChunkSection(y)->setTorchlight(x, y % CHUNK_SIZE, z, 0);
}

void Chunk::Render(MasterRenderer& renderer, Camera* camera) {
	TRY(
		for (ChunkSection& cs : sections) {

			if (cs.isUpdating() && camera->isBoxInFrustum(cs.getAABB()))
				renderer.ProcessChunkSection(cs);

			else if (cs.isMeshMade()) {
				if (!cs.isBuffered())
					cs.bufferMesh();

				if (camera->isBoxInFrustum(cs.getAABB()))
					renderer.ProcessChunkSection(cs);
			}
		}
	)
}

bool Chunk::makeMeshes() {
	TRY(
		for (ChunkSection& cs : sections) 
			if (!cs.isMeshMade()) {
				cs.buildMesh();
				return true;
			}

		hasMesh = true;
		return false;
	)
}

void Chunk::LoadLights() {
	TRY(
		for (int x = 0; x < CHUNK_SIZE; x++)
			for (int z = 0; z < CHUNK_SIZE; z++)
				setSunlight(x, getHeight(x, z), z, LIGHT_MAX);
	)
}

void Chunk::FinishLights() {

	return;

	while (!sunRemovalQueue.empty()) {
		TRY(
			if (&sunRemovalQueue.front() == nullptr)
				continue;

			glm::vec3	pos = sunRemovalQueue.front().first;
			short		val = sunRemovalQueue.front().second;

			Vector2 c = chunkCoord(pos.x, pos.z);
			Vector2 b = blockCoord(pos.x, pos.z);

			sunRemovalQueue.pop();

			auto TrySetLightValue = [&](const GLfloat& ox, const GLfloat& oy, const GLfloat& oz) {
				int neighborLevel = getSunlight(b.x + ox, pos.y + oy, b.z + oz);

				if (neighborLevel != 0 && neighborLevel < val) 
					world->resetSunlight(pos.x + ox, pos.y + oy, pos.z + oz);
				else if (neighborLevel >= val) 
					sunLightQueue.emplace(pos.x + ox, pos.y + oy, pos.z + oz);
			};

			TrySetLightValue(-1,  0,  0);
			TrySetLightValue( 1,  0,  0);
			TrySetLightValue( 0, -1,  0);
			TrySetLightValue( 0,  1,  0);
			TrySetLightValue( 0,  0, -1);
			TrySetLightValue( 0,  0,  1);
		)
	}

	while (!torchRemovalQueue.empty()) {
		TRY(
			if (&torchRemovalQueue.front() == nullptr)
				continue;

			glm::vec3	pos = torchRemovalQueue.front().first;
			short		val = torchRemovalQueue.front().second;

			Vector2 c = chunkCoord(pos.x, pos.z);
			Vector2 b = blockCoord(pos.x, pos.z);

			torchRemovalQueue.pop();

			auto TrySetLightValue = [&](const GLfloat& ox, const GLfloat& oy, const GLfloat& oz) {
				int neighborLevel = getTorchlight(b.x + ox, pos.y + oy, b.z + oz);

				if (neighborLevel != 0 && neighborLevel < val)
					world->resetTorchlight(pos.x + ox, pos.y + oy, pos.z + oz);
				else if (neighborLevel >= val)
					torchLightQueue.emplace(pos.x + ox, pos.y + oy, pos.z + oz);
			};

			TrySetLightValue(-1,  0,  0);
			TrySetLightValue( 1,  0,  0);
			TrySetLightValue( 0, -1,  0);
			TrySetLightValue( 0,  1,  0);
			TrySetLightValue( 0,  0, -1);
			TrySetLightValue( 0,  0,  1);
		)
	}

	while (!sunLightQueue.empty()) {
		TRY(
			if (&sunLightQueue.front() == nullptr)
				continue;

			glm::vec3 pos = sunLightQueue.front();
			Vector2		b = blockCoord(pos.x, pos.z);

			short	  val = getSunlight(b.x, pos.y, b.z);
			bool isOpaque = getBlock(b.x, pos.y, b.z).getData().opaque;

			sunLightQueue.pop();

			auto TrySetLightValue = [&](const GLfloat& ox, const GLfloat& oy, const GLfloat& oz) {
				if (isOpaque && !getBlock(b.x + ox, pos.y + oy, b.z + oz).getData().opaque)
					return;

				if (getSunlight(b.x + ox, pos.y + oy, b.z + oz) + 2 <= val)
					setSunlight(b.x + ox, pos.y + oy, b.z + oz, val - 1);
			};
		
			TrySetLightValue(-1,  0,  0);
			TrySetLightValue( 1,  0,  0);
			TrySetLightValue( 0, -1,  0);
			TrySetLightValue( 0,  1,  0);
			TrySetLightValue( 0,  0, -1);
			TrySetLightValue( 0,  0,  1);
		)
	}

	while (!torchLightQueue.empty()) {
		TRY(
			if (&torchLightQueue.front() == nullptr)
				continue;

			glm::vec3 pos = torchLightQueue.front();
			Vector2		b = blockCoord(pos.x, pos.z);

			short	  val = getTorchlight(b.x, pos.y, b.z);
			bool isOpaque = getBlock(b.x, pos.y, b.z).getData().opaque;

			torchLightQueue.pop();

			auto TrySetLightValue = [&](const GLfloat& ox, const GLfloat& oy, const GLfloat& oz) {
				if (isOpaque && !getBlock(b.x + ox, pos.y + oy, b.z + oz).getData().opaque)
					return;

				if (getTorchlight(b.x + ox, pos.y + oy, b.z + oz) + 2 <= val)
					world->setTorchlight(this->getPos().x * CHUNK_SIZE + b.x + ox, pos.y + oy, this->getPos().y * CHUNK_SIZE + b.z + oz, val - 1);
			};

			TrySetLightValue(-1,  0,  0);
			TrySetLightValue( 1,  0,  0);
			TrySetLightValue( 0, -1,  0);
			TrySetLightValue( 0,  1,  0);
			TrySetLightValue( 0,  0, -1);
			TrySetLightValue( 0,  0,  1);
		)
	}
}

void Chunk::save() {

	auto height = [=] {
		for (int x = 0; x < CHUNK_SIZE; x++)
			for (int z = 0; z < CHUNK_SIZE; z++)
				if (getHeight(x, z) != 0)
					return true;
		return false;
	};

	if (!height())
		return;

	std::string path("res/saves/" + worldPath + "/chunks/" + std::to_string(pos.x) + "  " + std::to_string(pos.y) + ".chunk");

	std::ofstream stream(path, std::ofstream::out | std::ofstream::trunc);

	if (!stream.is_open()) {
		std::cout << path << " save failed\n";
		return;
	}

	stream << sections.size() << "\n";

	for (auto& cs : sections) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++)
					stream << (int)cs.getBlock(x, y, z).id << " ";
				stream << "\t";
			}
			stream << "\n";
		}
		stream << "\n\n";
	}
	stream.close();
}

void Chunk::setUpdating(bool d) {
	updating = d;
	if (!loaded) {
		world->LoadChunk(pos.x, pos.y);
		LoadLights();
	}
}

bool Chunk::isUpdating() {
	return updating;
}

GLuint Chunk::getHeight(int x, int z) {

	if (outOfBound(x, z))
		return 0;

	return heights.getIndex(x, z);
}

GLuint Chunk::getMaxHeight() {
	return heights.getMaxValue();
}

void Chunk::setDeleted(bool d) {
	deleted = d;
}

bool Chunk::isDeleted() {
	return deleted;
}

bool Chunk::isLoaded() {
	return loaded;
}

bool Chunk::isMeshMade() {
	return hasMesh;
}

glm::ivec2& Chunk::getPos() {
	return pos;
}

AABB & Chunk::getAABB() {
	return aabb;
}
