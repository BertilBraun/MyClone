#pragma once

#include <SFML/Graphics.hpp>

class ToggleKey {
public:
	ToggleKey(sf::Keyboard::Key, float TTC = 0.2f);

	bool isKeyPressed();
	void resetTime();

private:
	sf::Keyboard::Key key;
	sf::Clock timer;
	float TTC;
};

class ToggleButton {
public:
	ToggleButton(sf::Mouse::Button, float TTC = 0.2f);

	bool isButtonPressed();
	void resetTime();

private:
	sf::Mouse::Button key;
	sf::Clock timer;
	float TTC;
};
