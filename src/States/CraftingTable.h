#pragma once

#include "StateBase.h"
#include "GUI/GUIComponent.h"
#include "Entity/Player.h"
#include "Inventory/Craft3x3.h"

class CraftingTable : public StateBase {
public:
	CraftingTable(Application& app, Player* player);
	~CraftingTable();

	void handleInput(float deltaTime, const Camera& camera) override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;
	void onResume() override;

private:
	TextureComponent invBackgound;
	Component selectedComp;
	Player* player;
	Craft3x3 craftingGrid;

};

