#pragma once
#include "StateBase.h"
#include "Application.h"

#include "World/World.h"
#include "World/WorldInfo/WorldInfo.h"
#include "World/Chunk/ChunkSection.h"

#include "Entity/Player.h"
#include "PlayerInventory.h"
#include "CraftingTable.h"

#include "Utils/ToggleKey.h"
#include "GUI/Button.h"

enum class PlayStates {
	NONE,
	INVENTORY,
	CRAFTING,

	NUM
};

class StatePlaying : public StateBase {
public:
	StatePlaying(Application& app, const std::string& path);
	~StatePlaying();

	void handleInput(float deltaTime, const Camera& camera) override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;

	void onResume() override;

	PlayStates state = PlayStates::NONE;
private:
	TextureComponent crosshair;
	WorldInfo worldInfo;
	World world;
	Player player;
	ToggleKey escape, inventory, craft;

	PlayerInventory invState;
	CraftingTable craftState;
};
