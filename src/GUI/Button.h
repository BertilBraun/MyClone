#pragma once

#include "GUIComponent.h"
#include "Utils/ToggleKey.h"
#include "SFML/Graphics.hpp"
#include <functional>

class Button : public GUIComponent {
public:
	Button(const glm::vec2& pos, const glm::vec2& size, const std::string& tex1, const std::string& tex2, const std::string& text, const sf::RenderWindow& window, std::function<void(void)> func = [&] {});

	void draw(MasterRenderer& renderer);

	bool pressed(const sf::RenderWindow& window);
	bool pressedR(const sf::RenderWindow& window);

	void setTexture(const sf::Texture& ntexture, const sf::RenderWindow& window);
	void setString(const std::string& ntext);
	void setPos(const glm::vec2& pos, const sf::RenderWindow& window);

	void resetButton();

private:
	std::function<void(void)> func;
	bool hovering = false;
	sf::Texture texture1, texture2;
	TextComponent text;
	ToggleButton leftButton, rightButton;
};