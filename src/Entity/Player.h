#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"
#include "Camera.h"
#include "Inventory/Inventory.h"
#include "World/WorldInfo/WorldInfo.h"

class World;
class MasterRenderer;
class ChunkBlock;

class Player : public MoveEntity {
public:
	Player(WorldInfo& info, World* world, Application* app);
	~Player();

	void KeyboardInput(const Camera& cam);
	void DisplayInformation(MasterRenderer& renderer, const Camera& cam, Application* app);

	bool removeOneFromHand();
	ChunkBlock getHeldBlock();
	Slot&		getCurrSlot();
	Inventory& getInventory();


private:
	sf::Text text;
	std::vector<TextureComponent> hpTex, noHpTex;
	float speed = 1;
	bool sprinting = false;
	Inventory inventory;
	World* world;
};

