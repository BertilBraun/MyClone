#pragma once

#include "GL/glew.h"

#include "DataBase/ID.h"
#include "AABB/AABB.h"

#include "Inventory/Slot.h"

#include <string>
#include <memory>
#include "glm/glm.hpp"

class Block {
public:
	Block(const std::string& path);
	void Init();
	
	ID id;

	glm::ivec2 textureUp;
	glm::ivec2 textureSide;
	glm::ivec2 textureDown;

	unsigned int stackSize = 1;
	std::string name;

	MeshType meshType = MeshType::BLOCK;
	BlockType blockType = BlockType::SOLID;

	AABB aabb;

	bool solid = false;
	bool opaque = false;

	unsigned short luminationFactor = 0;
	float breakTime = 1.0f;
	float demageOnHit = 0.0f;
	int blastResistance = 0;

	Slot drop;

private:
	char dc;
	int did, da;
};