#pragma once

#include "Model/Mesh.h"
#include "Model/Model.h"

struct ChunkMesh {
	Model model;
	Mesh mesh;
	GLuint index = 0, faces = 0;
};

struct ChunkMeshCollection {

	ChunkMesh world;
	ChunkMesh water;
	ChunkMesh leave;
};
