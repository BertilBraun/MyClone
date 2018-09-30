#pragma once

#include "GUI/Button.h"
#include "SFML/Window.hpp"
#include "Slot.h"

class Component {
public:
	Component(const glm::vec2& pos, const glm::vec2& size, const sf::RenderWindow& window);

	void draw(MasterRenderer& renderer);

	void update();

	bool pressed();
	bool pressedR();

	void setPos(const glm::vec2& pos);
	void setSlot(const Slot& s);

	void resetSlot();
	void removeOne();

	Slot slot;
private:
	const sf::RenderWindow& window;
	TextComponent slotNum;
	Button button;
};