#pragma once

#include "Application.h"
#include "Crafting/Recepies.h"
#include "Inventory.h"
#include "SFML/Window/Keyboard.hpp"
#include <vector>

class Craft3x3 {
public:
	Craft3x3(Application* app, Inventory* inv);

	void render(MasterRenderer& renderer);

	void update(Component& selectedComp);

	void tryRecepies();

private:
	std::vector<Component> comp;
	ToggleKey shift;
	Component result;
	Inventory* inv;
	Recepies recep;
	int SLOTS = 9;
};