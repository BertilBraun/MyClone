#include "ToggleKey.h"

ToggleKey::ToggleKey(sf::Keyboard::Key key, float TTC) : 
	key(key), 
	TTC(TTC) 
{ }

bool ToggleKey::isKeyPressed() {
	if (timer.getElapsedTime().asSeconds() > TTC)
		if (sf::Keyboard::isKeyPressed(key)) {
			timer.restart();
			return true;
		}
	
	return false;
}

void ToggleKey::resetTime() {
	timer.restart();
}

ToggleButton::ToggleButton(sf::Mouse::Button key, float TTC) :
	key(key),
	TTC(TTC)
{ }

bool ToggleButton::isButtonPressed() {
	if (timer.getElapsedTime().asSeconds() > TTC)
		if (sf::Mouse::isButtonPressed(key)) {
			timer.restart();
			return true;
		}

	return false;
}

void ToggleButton::resetTime() {
	timer.restart();
}
