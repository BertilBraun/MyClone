#pragma once

#include "World/World.h"
#include "World/Chunk/ChunkSection.h"

#include <vector>
#include <memory>

class ChunkMeshBuilder {
public:
	ChunkMeshBuilder(ChunkSection* cs, World* world);

	void buildMesh();

private:
	void TryAddFace(ChunkBlock block, const glm::ivec3& adj, const std::vector<GLfloat>& vertecies, const glm::ivec2& texCoord, const std::vector<GLfloat>& normals);
	bool shouldMakeFace(ChunkBlock block, glm::ivec3 adj);
	void AddData(const std::vector<GLfloat>& vertecies, const glm::ivec2& texCoord, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& lights);
	ChunkMesh* SetActiveMesh(ChunkBlock block);

	bool shouldCheckLayer(int y);
	
	struct adjBlock;
	ChunkSection* cs;
	World* world;
	ChunkMesh* activemesh;
};
