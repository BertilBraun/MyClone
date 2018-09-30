#pragma once
#include <SFML/Graphics.hpp>

class FPSCounter {
public:
	FPSCounter();

	void update();
	const sf::Text& getText() { return text; }

private:
	sf::Text text;

	sf::Clock delayTimer, fpsTimer;

	float fps = 0;
	int frameCount = 0;
};

