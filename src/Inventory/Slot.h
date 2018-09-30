#pragma once

#include "DataBase/ID.h"

class Material;
class Item;
class Block;

enum class SlotType {

	NONE,
	MATERIAL,
	BLOCK,
	ITEM,

	NUM
};

class Slot {
public:
	Slot();
	Slot(ID id, int a = 0);
	Slot(MID id, int a = 0);
	Slot(ItID id);
	
	int add(int a);
	bool removeOne();

	int getStackSize();
	void setStackSize(int i);
	int getMaxStackSize();
	int getID();

	void swapSlots(Slot& o);

	Block* block		= nullptr;
	Material* material	= nullptr;
	Item* item			= nullptr;

	SlotType type		= SlotType::NONE;

	bool operator==(const Slot& s);
	bool operator!=(const Slot& s);

private:
	int identfication	= 0;
	int maxStackSize	= 0;
	int stack			= 0;
};