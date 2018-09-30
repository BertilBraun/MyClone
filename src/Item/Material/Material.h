#pragma once

#include <string>
#include "glm/glm.hpp"

#include "DataBase/ID.h"

class Material {
public:
	Material(const std::string& path);

	MID id;
	glm::ivec2 invTexture;

	unsigned int stackSize = 1;
	std::string name = "Error";
};

