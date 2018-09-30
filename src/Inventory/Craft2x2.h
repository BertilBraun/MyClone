#pragma once

#include "Application.h"
#include "Crafting/Recepies.h"
#include "Inventory.h"
#include "SFML/Window/Keyboard.hpp"
#include <vector>

class Craft2x2 {
public:
	Craft2x2(Application* app, Inventory* inv);

	void render(MasterRenderer& renderer);

	void update(Component& selectedComp); 

	void tryRecepies(); 

private:
	std::vector<Component> comp;
	ToggleKey shift;
	Component result;
	Inventory* inv;
	Recepies recep;
	int SLOTS = 4;
};