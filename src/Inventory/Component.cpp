#include "Component.h"

Component::Component(const glm::vec2 & pos, const glm::vec2 & size, const sf::RenderWindow & window) :
	window(window),
	button(pos, size, "Transparent", "Transparent", "", window),
	slotNum(pos + glm::vec2(0.015, 0.01), size, "", window)
{ }


void Component::draw(MasterRenderer & renderer) {

	if (slot.type == SlotType::NONE)
		return;

	if ((slot.type == SlotType::BLOCK		&& slot.block->id != ID::Air) ||
		(slot.type == SlotType::MATERIAL	&& slot.material->id != MID::NONE) ||
		(slot.type == SlotType::ITEM		&& slot.item->id != ItID::NONE)) {

		//if (slot.type != SlotType::BLOCK)
		button.draw(renderer);
		slotNum.draw(renderer);
	}
}

void Component::update() {

	if (slot.type == SlotType::NONE)
		return;

	if ((slot.type == SlotType::BLOCK		 && slot.block->id != ID::Air) ||
		(slot.type == SlotType::MATERIAL	 && slot.material->id != MID::NONE) ||
		(slot.type == SlotType::ITEM		 && slot.item->id != ItID::NONE))
		slotNum.setString(std::to_string(slot.getStackSize()));

	if (slot.type == SlotType::BLOCK		 && slot.block->id != ID::Air)
		button.setTexture(DataBase::get().getTexture("Button"), window);

	else if (slot.type == SlotType::MATERIAL && slot.material->id != MID::NONE)
		button.setTexture(DataBase::get().getTexture(slot.material->name), window);

	else if (slot.type == SlotType::ITEM	 && slot.item->id != ItID::NONE)
		button.setTexture(DataBase::get().getTexture(slot.item->name), window);

	if (slot.type == SlotType::BLOCK		 && slot.block->id != ID::Air)
		button.setString(slot.block->name);

	else if (slot.type == SlotType::MATERIAL && slot.material->id != MID::NONE)
		button.setString(slot.material->name);

	else if (slot.type == SlotType::ITEM	 && slot.item->id != ItID::NONE)
		button.setString(slot.item->name);
}

bool Component::pressed() {
	return button.pressed(window);
}

bool Component::pressedR() {
	return button.pressedR(window);
}

void Component::setPos(const glm::vec2 & pos) {
	button.setPos(pos, window);
	slotNum.setPos(pos + glm::vec2(0.015, 0.01), window);
}

void Component::setSlot(const Slot & s) {
	slot = s;
	update();
}

void Component::resetSlot() {
	slot = Slot();
	update();
}

void Component::removeOne() {
	if (!slot.removeOne())
		slot = Slot();
	update();
}
