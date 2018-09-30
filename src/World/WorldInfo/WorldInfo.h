#pragma once

#include <string>
#include "glm/glm.hpp"


class Player;

class WorldInfo {
public:
	WorldInfo(const std::string& path);
	~WorldInfo();

	bool Save(Player& player);

	glm::vec3 pos;
	bool setPosition = false;

	int seed;
	std::string path;
};