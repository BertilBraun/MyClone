#include "Entity.h"

#include "World/World.h"

void MoveEntity::Update(float deltaTime, World * world) {
	
	vel.x *= 0.7f;
	vel.z *= 0.7f;
	if (swimming)
		vel -= GRAVITY * 0.2f * deltaTime;
	else
		vel -= GRAVITY * deltaTime;

	glm::vec3 updateVel = vel * deltaTime * Config::get().movementSpeed;
	swimming = false;

	if (pos.y > heighestPoint)
		heighestPoint = pos.y;

	pos.y += updateVel.y;
	if (collision(world, pos, deltaTime, true)) {
		pos.y -= updateVel.y;
		vel.y = 0;

		if (heighestPoint - pos.y > 3 && !swimming) 
			health = std::max(0.0f, health - ((heighestPoint - pos.y) * 0.4f));
		heighestPoint = pos.y;
	}

	pos.x += updateVel.x;
	if (collision(world, pos, deltaTime))
		pos.x -= updateVel.x;

	pos.z += updateVel.z;
	if (collision(world, pos, deltaTime))
		pos.z -= updateVel.z;

	if (pos.y < -10)
		pos = world->getSpawnPoint();
}

bool MoveEntity::collision(World * world, const glm::vec3& pos, float deltaTime, bool checkOnGround) {

	box.UpdatePos(pos - (box.dim / 2.0f));

	for (int x = (int)box.min.x; x <= (int)box.max.x; x++)
		for (int y = (int)(box.min.y - 0.7f); y <= (int)box.max.y; y++)
			for (int z = (int)box.min.z; z <= (int)box.max.z; z++) {

				if (world->getBlock(x, y, z).getData().demageOnHit)
					health -= world->getBlock(x, y, z).getData().demageOnHit * deltaTime * 10;

				if (world->getBlock(x, y, z).getData().blockType == BlockType::FLUID)
					swimming = true;

				if (world->getBlock(x, y, z).getData().solid) {
					if (y == (int)(box.min.y - 0.7f) && checkOnGround)
						onGround = true;
					return true;
				}
				//if (box.Collided(world->getBlock(x, y, z).getData().aabb))
				//	return true;
			}
	return false;
}
void MoveEntity::removeHealth(float a) {
	health = std::min(std::max(health - a, (float)0), (float)MAX_HP);
}

int MoveEntity::getHealth() {
	return health;
}

MoveEntity::MoveEntity(const glm::vec3 & dim) :
	box(dim)
{ }

AABB & MoveEntity::getAABB() {
	return box;
}

glm::vec3 MoveEntity::getVel() {
	return vel;
}

void MoveEntity::setVel(const glm::vec3 & vel) {
	this->vel = vel;
}
