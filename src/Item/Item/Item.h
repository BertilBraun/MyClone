#pragma once

#include "DataBase/ID.h"
#include "glm/glm.hpp"
#include <string>

class Item {
public:
	Item(const std::string& path);
	Item(ItID id = ItID::NONE, float breakMultiplier = 1.0f, unsigned int attackValue = 0, int hp = 1);

	ItID id;

	std::string name = "NONAME";

	glm::ivec2 invTexture;

	float breakMultiplier = 1;
	unsigned int attackValue = 0;
	int hp = 1;

private:

};