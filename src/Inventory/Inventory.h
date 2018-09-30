#pragma once

#include "Slot.h"
#include "DataBase/DataBase.h"
#include "GUI/Button.h"
#include "Component.h"

class MasterRenderer;

class Inventory {
public:
	Inventory(Application* app, const std::string& path, int INV_SIZE, int INV_DISPLAY_SIZE);
	~Inventory();

	bool tryToRemove(ItID id);
	int tryToRemove(ID id, int ammount);
	int tryToRemove(MID id, int ammount);

	bool add(Slot& s);
	bool add(ItID id);
	int add(ID id, int ammount);
	int add(MID id, int ammount);

	void render(MasterRenderer& renderer);
	void Update();

	Slot& currSlot();
	int getCurrentSlot();

	Slot& operator[](int i);

	int getInvSize();
	Component& getComp(int i);

	void resetSlot(int i);
	void setSlot(int i, const Slot& s);
	void updateSlot(int i);

	bool load(const std::string& path);

protected:
	const int INV_SIZE, INV_DISPLAY_SIZE;
	int currentSlot = 0;
	Application* app;
	std::vector<Component> comp, dispComp;
	TextureComponent hotbar, selectedSlot;
};

