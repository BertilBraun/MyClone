#include "Slot.h"

#include <iostream>

#include "DataBase/DataBase.h"
#include "Item/Material/Material.h"
#include "Item/Item/Item.h"

Slot::Slot() :
	maxStackSize(0),
	stack(0)
{
	identfication = -1;
}

Slot::Slot(ID id, int a) :
	type(SlotType::BLOCK),
	block(&DataBase::get().getBlock(id)),
	maxStackSize(block->stackSize),
	stack(std::min(a, maxStackSize))
{ 
	identfication = (int)id;
}

Slot::Slot(MID id, int a) :
	type(SlotType::MATERIAL),
	material(&DataBase::get().getMaterial(id)),
	maxStackSize(material->stackSize),
	stack(std::min(a, maxStackSize))
{
	identfication = (int)id + 1000;
}

Slot::Slot(ItID id) :
	type(SlotType::ITEM),
	item(&DataBase::get().getItem(id)),
	maxStackSize(1),
	stack(1)
{ 
	identfication = (int)id + 2000;
}

int Slot::add(int a) {

	stack += a;
	
	if (stack > maxStackSize) {
		int val = stack - maxStackSize;
		stack = maxStackSize;
		return val;
	}
	return 0;
}

bool Slot::removeOne() {
	if (stack > 0)
		stack--;
	return stack > 0;
}

int Slot::getStackSize() {
	return stack;
}

void Slot::setStackSize(int i) {
	stack = std::min(i, maxStackSize);
}

int Slot::getMaxStackSize() {
	return maxStackSize;
}

int Slot::getID() {
	return identfication;
}

void Slot::swapSlots(Slot & o) {
	std::swap(*this, o);
}

bool Slot::operator==(const Slot & s) {
	return type == s.type && (
		(type == SlotType::BLOCK	&& block->id == s.block->id) ||
		(type == SlotType::MATERIAL	&& material->id == s.material->id) ||
		(type == SlotType::ITEM		&& item->id == s.item->id) ||
		(type == SlotType::NONE		&& s.type == SlotType::NONE));
}

bool Slot::operator!=(const Slot & s) {
	return type != s.type || item != s.item || block != s.block || material != s.material;
}