#include "GUIComponent.h"

GUIComponent::GUIComponent(const glm::vec2 & pos, const glm::vec2 & size, const sf::RenderWindow & window) :
	pos(pos),
	size(size)
{
	rect.setSize({ size.x * window.getViewport(window.getView()).width, size.y * window.getViewport(window.getView()).height });
	rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
	rect.setPosition(pos.x * window.getViewport(window.getView()).width, pos.y * window.getViewport(window.getView()).height);
}

void GUIComponent::draw(MasterRenderer & renderer) {
	renderer.ProcessSFML(rect);
}

void GUIComponent::setPos(const glm::vec2 & pos, const sf::RenderWindow & window) {
	rect.setPosition(pos.x * window.getViewport(window.getView()).width, pos.y * window.getViewport(window.getView()).height);
}

void GUIComponent::setSize(const glm::vec2 & size, const sf::RenderWindow & window) {
	rect.setSize({ size.x * window.getViewport(window.getView()).width, size.y * window.getViewport(window.getView()).height });
	rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
}

TextureComponent::TextureComponent(const glm::vec2 & pos, const glm::vec2 & size, const std::string & texturepath, const sf::RenderWindow & window) :
	GUIComponent(pos, size, window)
{
	if (!texture.loadFromFile("res/Textures/" + texturepath))
		throw std::runtime_error("didnt load" + texturepath);
	rect.setTexture(&texture);
}

void TextureComponent::setTexture(const sf::Texture & texture, const sf::RenderWindow & window) {
	this->texture = texture;
}

TextComponent::TextComponent(const glm::vec2 & pos, const glm::vec2 & size, const std::string & text, const sf::RenderWindow & window) :
	Text(DataBase::get().getText())
{
	Text.setString(text);
	Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height / 2);
	Text.setPosition(pos.x * window.getViewport(window.getView()).width, pos.y * window.getViewport(window.getView()).height);
}

void TextComponent::setString(const std::string & text) {
	if (text == Text.getString())
		return;
	Text.setString(text);
	Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height / 2);
}

void TextComponent::setPos(const glm::vec2 & pos, const sf::RenderWindow & window) {
	Text.setPosition(pos.x * window.getViewport(window.getView()).width, pos.y * window.getViewport(window.getView()).height);
}

void TextComponent::draw(MasterRenderer & renderer) {
	renderer.ProcessSFML(Text);
}
