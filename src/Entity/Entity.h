#pragma once

#include "glm/glm.hpp"
#include "AABB/AABB.h"
#include "Extern/Config.h"
#include "defines.h"

class World;

struct Entity {

	glm::vec3 getPos() { return pos; }
	glm::vec3 getRot() { return rot; }

	void setPos(const glm::vec3& pos) { this->pos = pos; }
	void setRot(const glm::vec3& rot) { this->pos = rot; }

protected:
	glm::vec3 pos = glm::vec3(0);
	glm::vec3 rot = glm::vec3(0);

};

struct MoveEntity : public Entity {
	MoveEntity(const glm::vec3& dim = { 1, 1, 1 });

	AABB& getAABB();

	glm::vec3 getVel();
	void setVel(const glm::vec3& vel);

	void Update(float deltaTime, World* world); 
	bool collision(World * world, const glm::vec3& pos, float deltaTime = 1.0f, bool checkOnGround = false);

	void removeHealth(float a);
	int getHealth();

protected:
	bool onGround = false, swimming = false, canFly = false;
	glm::vec3 vel = glm::vec3(0);
	AABB box;
	float health = MAX_HP, heighestPoint = 0;
};

