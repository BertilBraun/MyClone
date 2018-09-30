#pragma once

#include "StateBase.h"
#include "GUI/GUIComponent.h"
#include "Entity/Player.h"
#include "Inventory/Craft2x2.h"

class PlayerInventory : public StateBase {
public:

	PlayerInventory(Application& app, Player* player);
	~PlayerInventory();

	void handleInput(float deltaTime, const Camera& camera) override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;
	void onResume() override;

private:
	TextureComponent invBackgound;
	Component selectedComp;
	Player* player;
	Craft2x2 craftingGrid;
};