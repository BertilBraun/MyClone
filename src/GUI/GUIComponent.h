#pragma once
#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"

#include "Renderer/MasterRenderer.h"
#include "DataBase/DataBase.h"

class GUIComponent {
public:
	GUIComponent(const glm::vec2& pos, const glm::vec2& size, const sf::RenderWindow& window);

	virtual void draw(MasterRenderer& renderer);

	void setPos(const glm::vec2& pos, const sf::RenderWindow& window);
	void setSize(const glm::vec2& size, const sf::RenderWindow& window);

protected:
	sf::RectangleShape rect;
	glm::vec2 pos, size;
};

class TextureComponent : public GUIComponent {
public:
	TextureComponent(const glm::vec2& pos, const glm::vec2& size, const std::string& texturepath, const sf::RenderWindow& window);
	
	void setTexture(const sf::Texture& texture, const sf::RenderWindow& window);

private:
	sf::Texture texture;
};

class TextComponent {
public:
	TextComponent(const glm::vec2& pos, const glm::vec2& size, const std::string& text, const sf::RenderWindow& window);

	void setString(const std::string& text);
	void setPos(const glm::vec2& pos, const sf::RenderWindow& window);

	void draw(MasterRenderer& renderer);

private:
	sf::Text Text;
};