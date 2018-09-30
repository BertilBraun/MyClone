#pragma once

#include "WorldEvent.h"

#include "World/World.h"
#include "Entity/Player.h"

#include "Math/Ray.h"
#include "Event.h"


#include "SFML/System/Clock.hpp"

class BlockBreakEvent : public WorldEvent {
public:
	BlockBreakEvent(World* world, Camera* camera, Player* player) :
		WorldEvent(EventType::BREAK),
		world(world),
		camera(camera),
		player(player)
	{
		forward = glm::normalize(camera->forward);

		for (Ray ray(camera->getPos(), forward); ray.getLength() < DIG_DISTANCE; ray.Step(STEP_SIZE)) {

			d = glm::ivec3(ray.getEnd());

			ChunkBlock block = world->getBlock(d.x, d.y, d.z);

			if (block.id != ID::Air && block.getData().blockType != BlockType::FLUID) {
				TimeToComplete = block.getData().breakTime;

				slot = player->getCurrSlot();
				if (slot.type == SlotType::ITEM)
					TimeToComplete *= slot.item->breakMultiplier;

				break;
			}
		}

		if (TimeToComplete == 0 || d.y == 0)
			done = true;
	}

	bool Update(float deltaTime) {

		TimeSinceStart += deltaTime;

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) || done || slot != player->getCurrSlot())
			return true;

		glm::vec3 nforward = glm::normalize(camera->forward);

		if (nforward != forward) {

			forward = nforward;

			if (RayCast(world).cast(camera->getPos(), forward) != d)
				return true;
		}

		if (TimeSinceStart > TimeToComplete) {

			ChunkBlock block = world->getBlock(d.x, d.y, d.z);

			if (block.id != ID::Air && block.getData().blockType != BlockType::FLUID) {

				player->getInventory().add(block.getData().drop);

				world->UpdateChunk		(d.x, d.y, d.z);
				world->setBlock			(d.x, d.y, d.z, ID::Air);
				world->resetSunlight	(d.x, d.y, d.z);
				world->resetTorchlight	(d.x, d.y, d.z);
			}
			return true;
		}
		return false;
	}

	void Display(MasterRenderer& renderer) {
		renderer.ProcessBreakAnim(glm::vec3(d), TimeSinceStart / TimeToComplete);
	}
		
private:
	float	TimeSinceStart = 0,
			TimeToComplete = 0;
	bool done = false;
	glm::vec3 forward;
	glm::ivec3 d;
	Slot slot;
	World * world;
	Camera* camera;
	Player* player;
};