#pragma once

#include "WorldEvent.h"

#include "World/World.h"
#include "Entity/Player.h"

#include "Math/Ray.h"
#include "Event.h"

#include "SFML/System/Clock.hpp"

class BlockPlaceEvent : public WorldEvent {
public:
	BlockPlaceEvent(World* world, Camera* camera, Player* player) :
		WorldEvent(EventType::PLACE),
		world(world),
		camera(camera),
		player(player)
	{ }

	bool Update(float deltaTime) {

		if (player->getHeldBlock().id == ID::Air)
			return true;

		glm::vec3 forward = glm::normalize(camera->forward);

		for (Ray ray(camera->getPos(), forward); ray.getLength() < DIG_DISTANCE; ray.Step(STEP_SIZE)) {

			glm::vec3  pos(ray.getEnd());
			glm::ivec3 ipos(ray.getEnd());

			ChunkBlock block = world->getBlock(ipos.x, ipos.y, ipos.z);

			if (block.id != ID::Air && block.getData().blockType != BlockType::FLUID) {

				ipos  = glm::ivec3(pos - forward * STEP_SIZE);
				block = world->getBlock(ipos.x, ipos.y, ipos.z);

				world->setBlock(ipos.x, ipos.y, ipos.z, player->getHeldBlock().id);

				if (player->collision(world, player->getPos())) {

					world->setBlock(ipos.x, ipos.y, ipos.z, ID::Air);
					world->setSunlight(ipos.x, ipos.y, ipos.z, block.getSunlight());
					world->setTorchlight(ipos.x, ipos.y, ipos.z, block.getTorchlight());

				} else {

					if (player->removeOneFromHand())
						return true;

					world->UpdateChunk(ipos.x, ipos.y, ipos.z);

					world->resetSunlight(ipos.x, ipos.y, ipos.z);
					world->resetTorchlight(ipos.x, ipos.y, ipos.z);

					if (world->getHeight(ipos.x, ipos.z) == ipos.y) {

						for (int i = 0; i < world->getHeight(ipos.x, ipos.z); i++) {
							world->resetSunlight(ipos.x, i, ipos.z);
							world->resetTorchlight(ipos.x, i, ipos.z);
						}

						int height = (	world->getHeight(ipos.x, ipos.z) +
										world->getHeight(ipos.x + 1, ipos.z) +
										world->getHeight(ipos.x - 1, ipos.z) +
										world->getHeight(ipos.x, ipos.z + 1) +
										world->getHeight(ipos.x, ipos.z - 1)) / 5;

						if (ipos.y >= height)
							world->setSunlight(ipos.x, ipos.y, ipos.z, LIGHT_MAX);
						else
							world->setSunlight(ipos.x, ipos.y, ipos.z, std::max(ipos.y - height, 0));
					}
				}
				return true;
			}
		}
		return true;
	}

private:
	World * world;
	Camera* camera;
	Player* player;
};