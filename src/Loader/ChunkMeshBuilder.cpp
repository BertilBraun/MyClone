#include "ChunkMeshBuilder.h"
#include "Loader.h"

#include "SFML/System/Clock.hpp"
#include "Utils/UtilityFunctions.h"

#include "Texture/TextureAtlas.h"

namespace {
	const std::vector<GLfloat> topN{
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0
	};

	const std::vector<GLfloat> downN{
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0
	};

	const std::vector<GLfloat> northN{
		0,0,-1,
		0,0,-1,
		0,0,-1,
		0,0,-1
	};

	const std::vector<GLfloat> eastN{
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0
	};

	const std::vector<GLfloat> southN{
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1
	};

	const std::vector<GLfloat> westN{
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0
	};

	std::vector<GLfloat> south(const glm::vec3& off) {
		return {
			0 + off.x, 0 + off.y, 1 + off.z,
			1 + off.x, 0 + off.y, 1 + off.z,
			1 + off.x, 1 + off.y, 1 + off.z,
			0 + off.x, 1 + off.y, 1 + off.z
		};
	}

	std::vector<GLfloat> north(const glm::vec3& off) {
		return {
			1 + off.x, 0 + off.y, 0 + off.z,
			0 + off.x, 0 + off.y, 0 + off.z,
			0 + off.x, 1 + off.y, 0 + off.z,
			1 + off.x, 1 + off.y, 0 + off.z
		};
	}

	std::vector<GLfloat> east(const glm::vec3& off) {
		return {
			1 + off.x, 0 + off.y, 1 + off.z,
			1 + off.x, 0 + off.y, 0 + off.z,
			1 + off.x, 1 + off.y, 0 + off.z,
			1 + off.x, 1 + off.y, 1 + off.z
		};
	}

	std::vector<GLfloat> west(const glm::vec3& off) {
		return {
			0 + off.x, 0 + off.y, 0 + off.z,
			0 + off.x, 0 + off.y, 1 + off.z,
			0 + off.x, 1 + off.y, 1 + off.z,
			0 + off.x, 1 + off.y, 0 + off.z
		};
	}

	std::vector<GLfloat> top(const glm::vec3& off) {
		return {
			0 + off.x, 1 + off.y, 1 + off.z,
			1 + off.x, 1 + off.y, 1 + off.z,
			1 + off.x, 1 + off.y, 0 + off.z,
			0 + off.x, 1 + off.y, 0 + off.z
		};
	}

	std::vector<GLfloat> bottom(const glm::vec3& off) {
		return {
			0 + off.x, 0 + off.y, 0 + off.z,
			1 + off.x, 0 + off.y, 0 + off.z,
			1 + off.x, 0 + off.y, 1 + off.z,
			0 + off.x, 0 + off.y, 1 + off.z
		};
	}

	std::vector<GLfloat> XmeshOne(const glm::vec3& off) {
		return {
			0 + off.x, 0 + off.y, 0 + off.z,
			1 + off.x, 0 + off.y, 1 + off.z,
			1 + off.x, 1 + off.y, 1 + off.z,
			0 + off.x, 1 + off.y, 0 + off.z
		};
	}

	std::vector<GLfloat> XmeshTwo(const glm::vec3& off) {
		return {
			0 + off.x, 0 + off.y, 1 + off.z,
			1 + off.x, 0 + off.y, 0 + off.z,
			1 + off.x, 1 + off.y, 0 + off.z,
			0 + off.x, 1 + off.y, 1 + off.z
		};
	}
}

struct ChunkMeshBuilder::adjBlock {

	void update(int x, int y, int z) {
		up		= { x, y + 1, z };
		right	= { x + 1, y, z };
		left	= { x - 1, y, z };
		front	= { x, y, z + 1 };
		back	= { x, y, z - 1 };
		down	= { x, y - 1, z };
	}

	glm::ivec3	up		,
				right	,
				left	,
				front	,
				back	,
				down	;
};

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection* cs, World* world) :
	cs(cs), 
	world(world) 
{ }

void ChunkMeshBuilder::buildMesh() {
	TRY(
		glm::vec3 blockPos;
		ChunkBlock block;
		Block* data;
		adjBlock adj;

		auto reset = [](ChunkMesh& mesh) {
			mesh.faces = 0;
			mesh.index = 0;
			mesh.mesh.indicies.clear();
			mesh.mesh.verticies.clear();
			mesh.mesh.textures.clear();
			mesh.mesh.normals.clear();
			mesh.mesh.lights.clear();
		};

		ChunkMeshCollection& coll = cs->getMeshes();

		reset(coll.world);
		reset(coll.water);
		reset(coll.leave);

		sf::Clock c;

		for (int y = 0; y < CHUNK_SIZE; y++) {

			if (!shouldCheckLayer(y))
				continue;

			for (int x = 0; x < CHUNK_SIZE; x++) 
				for (int z = 0; z < CHUNK_SIZE; z++) {
					
					block = cs->getBlock(x, y, z);

					if (block.id == ID::Air)
						continue;

					activemesh = SetActiveMesh(block);					

					blockPos = glm::vec3((cs->getPos() * CHUNK_SIZE) + glm::ivec3(x, y, z));
					data = &block.getData();
				
					if (data->meshType == MeshType::BLOCK) {

						adj.update(x, y, z);

						if (y + cs->getPos().y != 0)
							TryAddFace(block, adj.down, bottom(blockPos),	data->textureDown, downN);
						TryAddFace(block, adj.up,		top(blockPos),		data->textureUp,   topN);

						TryAddFace(block, adj.right,	east(blockPos),		data->textureSide, eastN);
						TryAddFace(block, adj.left,		west(blockPos),		data->textureSide, westN);

						TryAddFace(block, adj.front,	south(blockPos),	data->textureSide, southN);
						TryAddFace(block, adj.back,		north(blockPos),	data->textureSide, northN);
					}
					else if (data->meshType == MeshType::X) {
						AddData(XmeshOne(blockPos), data->textureSide, {0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0}, { (GLfloat)block.getSunlight(), (GLfloat)block.getTorchlight() });
						AddData(XmeshTwo(blockPos), data->textureSide, {0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0}, { (GLfloat)block.getSunlight(), (GLfloat)block.getTorchlight() });
					}
					else {
						std::cout << DataBase::get().getBlock(block.id).name << " : " << (int)block.getData().meshType << "\n";
					}
				}
		}
/*
	if (!cs->getMeshes().world.faces && !cs->getMeshes().water.faces && !cs->getMeshes().leave.faces && c.getElapsedTime().asMilliseconds() > 50)
		return;

	std::cout <<	"World : " << cs->getMeshes().world.faces << " faces! \n" <<
					"Water : " << cs->getMeshes().water.faces << " faces! \n" <<
					"Leave : " << cs->getMeshes().leave.faces << " faces! \n" <<
					"took : " << c.getElapsedTime().asMilliseconds() << "ms\n\n";
*/
	);
}


void ChunkMeshBuilder::TryAddFace(ChunkBlock block, const glm::ivec3& adj, const std::vector<GLfloat>& vertecies, const glm::ivec2& texCoord, const std::vector<GLfloat>& normals) {

	if (shouldMakeFace(block, adj))
		AddData(vertecies, texCoord, normals, { (GLfloat)block.getSunlight(), (GLfloat)block.getTorchlight() }); 
}

bool ChunkMeshBuilder::shouldMakeFace(ChunkBlock block, glm::ivec3 adj) {

	if (block.getData().blockType == BlockType::FLUID && 
		cs->getBlock(adj.x, adj.y, adj.z).getData().blockType == BlockType::FLUID)
		return false;

	if (!cs->getBlock(adj.x, adj.y, adj.z).getData().opaque)
		return true;

	return false;
}

ChunkMesh* ChunkMeshBuilder::SetActiveMesh(ChunkBlock block) {

	switch (block.getData().blockType) {
	case BlockType::SOLID:
		return &cs->getMeshes().world;

	case BlockType::FLUID:
		return &cs->getMeshes().water;

	case BlockType::LEAVE:
		return &cs->getMeshes().leave;
	}
	return nullptr;
}

void ChunkMeshBuilder::AddData(const std::vector<GLfloat>& vertecies, const glm::ivec2& texCoord, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& lights) {

	auto insert = [](std::vector<GLfloat>& toAdd, const std::vector<GLfloat>& value) {	
		toAdd.insert(toAdd.end(), value.begin(), value.end());
	};

	Mesh& mesh = activemesh->mesh;
	GLuint& index = activemesh->index;

	insert(mesh.verticies, vertecies);
	insert(mesh.textures, TextureAtlas::get().GetTextureCoords(texCoord));
	insert(mesh.normals, normals);
	insert(mesh.lights, {	lights[0],lights[1],
							lights[0],lights[1],
							lights[0],lights[1],
							lights[0],lights[1] });

	mesh.indicies.insert(mesh.indicies.end(), {	0 + index, 1 + index, 2 + index,
												2 + index, 3 + index, 0 + index	});

	index += 4;
	activemesh->faces++;
}

bool ChunkMeshBuilder::shouldCheckLayer(int y) {
	
	glm::ivec3 c = cs->getPos();

	return (!cs->allSolid(y) ||
			!cs->allSolid(y - 1) ||
			!cs->allSolid(y + 1) ||
			!world->getChunk(c.x - 1, c.z)->getChunkSection(c.y * CHUNK_SIZE)->allSolid(y) ||
			!world->getChunk(c.x + 1, c.z)->getChunkSection(c.y * CHUNK_SIZE)->allSolid(y) ||
			!world->getChunk(c.x, c.z - 1)->getChunkSection(c.y * CHUNK_SIZE)->allSolid(y) ||
			!world->getChunk(c.x, c.z + 1)->getChunkSection(c.y * CHUNK_SIZE)->allSolid(y));
}