#include "ChunkSection.h"

#include <algorithm>

#include "Loader/Loader.h"
#include "Loader/ChunkMeshBuilder.h"
#include "Utils/Mutexes.h"

#include "Chunk.h"
#include "World/World.h"

#include "Utils/UtilityFunctions.h"

void Layer::update(ChunkBlock cb) {

	cb.getData().opaque ?
		anzSolids++ :
		anzSolids--;

	anzSolids = std::max(std::min(anzSolids, CHUNK_AREA), 0);
}

bool Layer::allSolid() {
	return anzSolids == CHUNK_AREA;
}

ChunkSection::ChunkSection(World* world, const glm::ivec3& pos) : 
	world(world), 
	pos(pos),
	aabb({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE})
{
	aabb.UpdatePos(glm::vec3(pos * CHUNK_SIZE));
	blocks.fill(ID::Air);
}

ChunkSection::~ChunkSection() {
}

ChunkBlock ChunkSection::getBlock(int bx, int by, int bz) {

	if (outOfChunkRange(bx) || outOfChunkRange(by) || outOfChunkRange(bz))
		return world->getBlock(bx + pos.x * CHUNK_SIZE, by + pos.y * CHUNK_SIZE, bz + pos.z * CHUNK_SIZE);

	return blocks.getIndex(bx, by, bz);
}

void ChunkSection::setBlock(int bx, int by, int bz, ID ID) {

	if (outOfChunkRange(bx) || outOfChunkRange(by) || outOfChunkRange(bz))
		world->setBlock(bx + pos.x * CHUNK_SIZE, by + pos.y * CHUNK_SIZE, bz + pos.z * CHUNK_SIZE, ID);

	MUTEX(Mutexes::get().blockMutex,
		layers[by].update(ID);
		blocks.setIndex(bx, by, bz, ID);
		blocks.getIndex(bx, by, bz).getData().aabb.UpdatePos(glm::vec3(pos * CHUNK_SIZE) + glm::vec3(bx, by, bz));
	);
}

void ChunkSection::buildMesh() {

	ChunkMeshBuilder(this, world).buildMesh();
	buffered = false;
	updating = false;
	meshMade = true;
}

void ChunkSection::bufferMesh() {

	Loader::get().BufferMesh(*this);
	buffered = true;
}

int ChunkSection::getSunlight(int x, int y, int z) {
	if (outOfChunkRange(x) || outOfChunkRange(y) || outOfChunkRange(z))
		return world->getSunlight(x + pos.x * CHUNK_SIZE, y + pos.y * CHUNK_SIZE, z + pos.z * CHUNK_SIZE);

	return blocks.getIndex(x, y, z).getSunlight();
}

void ChunkSection::setSunlight(int x, int y, int z, int val) {
	if (outOfChunkRange(x) || outOfChunkRange(y) || outOfChunkRange(z))
		world->setSunlight(x + pos.x * CHUNK_SIZE, y + pos.y * CHUNK_SIZE, z + pos.z * CHUNK_SIZE, val);
	
	MUTEX(Mutexes::get().blockMutex,
		blocks.getIndex(x, y, z).setSunlight(val);
	);
}

int ChunkSection::getTorchlight(int x, int y, int z) {
	if (outOfChunkRange(x) || outOfChunkRange(y) || outOfChunkRange(z))
		return world->getTorchlight(x + pos.x * CHUNK_SIZE, y + pos.y * CHUNK_SIZE, z + pos.z * CHUNK_SIZE);

	return blocks.getIndex(x, y, z).getTorchlight();
}

void ChunkSection::setTorchlight(int x, int y, int z, int val) {
	if (outOfChunkRange(x) || outOfChunkRange(y) || outOfChunkRange(z))
		world->setTorchlight(x + pos.x * CHUNK_SIZE, y + pos.y * CHUNK_SIZE, z + pos.z * CHUNK_SIZE, val);

	MUTEX(Mutexes::get().blockMutex,
		blocks.getIndex(x, y, z).setTorchlight(val);
	);
}

bool ChunkSection::allSolid(int y) {
	if (y == -1) {
		if (pos.y > 0)
			return world->getChunk(pos.x, pos.z)->getChunkSection((pos.y - 1) * CHUNK_SIZE)->allSolid(CHUNK_SIZE - 1);
		else
			return false;
	}

	if (y == CHUNK_SIZE)
		return world->getChunk(pos.x, pos.z)->getChunkSection((pos.y + 1) * CHUNK_SIZE)->allSolid(0);

	return layers[y].allSolid();
}

ChunkMeshCollection & ChunkSection::getMeshes() {
	return meshCollection;
}

glm::ivec3& ChunkSection::getPos() {
	return pos;
}

AABB & ChunkSection::getAABB() {
	return aabb;
}

bool ChunkSection::isBuffered() {
	return buffered;
}

bool ChunkSection::isMeshMade() {
	return meshMade;
}

bool ChunkSection::isUpdating() { 
	return updating;
}

void ChunkSection::setUpdating(bool v) {
	updating = v; 
	world->getChunk(pos.x, pos.z)->setUpdating(true);
}

