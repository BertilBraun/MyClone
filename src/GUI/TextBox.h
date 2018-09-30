#pragma once

#include "GUIComponent.h"
#include "Utils/ToggleKey.h"

class TextBox {
public:
	TextBox(const glm::vec2& pos, const glm::vec2& size, const std::string& texturepath, const sf::RenderWindow& window);

	void Update();
	void draw(MasterRenderer& renderer);

	std::string getText();
	void addCharToString(char c);

private:
	TextComponent textComponent;
	TextureComponent textureComponent;
	std::string Text;
	std::vector<ToggleKey> keys;
};