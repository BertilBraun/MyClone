#include "Button.h"

Button::Button(const glm::vec2 & pos, const glm::vec2 & size, const std::string & tex1, const std::string & tex2, const std::string & text, const sf::RenderWindow & window, std::function<void(void)> func) :
	GUIComponent(pos, size, window),
	text(pos - glm::vec2(0, 0.005), size, text, window),
	leftButton(sf::Mouse::Button::Left, 0.2f),
	rightButton(sf::Mouse::Button::Right, 0.2f),
	func(func)
{
	texture1 = DataBase::get().getTexture(tex1);
	texture2 = DataBase::get().getTexture(tex2);
}

void Button::draw(MasterRenderer & renderer) {
	if (!hovering)
		rect.setTexture(&texture1, true);
	else
		rect.setTexture(&texture2, true);

	GUIComponent::draw(renderer);

	text.draw(renderer);
}

bool Button::pressed(const sf::RenderWindow & window) {

	hovering = false;

	sf::Vector2i mPos = sf::Mouse::getPosition(window);

	if (mPos.x >= rect.getPosition().x - rect.getGlobalBounds().width / 2
		&& mPos.x <= rect.getPosition().x + rect.getGlobalBounds().width / 2
		&& mPos.y >= rect.getPosition().y - rect.getGlobalBounds().height / 2
		&& mPos.y <= rect.getPosition().y + rect.getGlobalBounds().height / 2)
		hovering = true;

	if (hovering && leftButton.isButtonPressed()) {
		func();
		return true;
	}
	return false;
}

bool Button::pressedR(const sf::RenderWindow & window) {

	hovering = false;

	sf::Vector2i mPos = sf::Mouse::getPosition(window);

	if (mPos.x >= rect.getPosition().x - rect.getGlobalBounds().width / 2
		&& mPos.x <= rect.getPosition().x + rect.getGlobalBounds().width / 2
		&& mPos.y >= rect.getPosition().y - rect.getGlobalBounds().height / 2
		&& mPos.y <= rect.getPosition().y + rect.getGlobalBounds().height / 2)
		hovering = true;

	if (hovering && rightButton.isButtonPressed()) {
		func();
		return true;
	}
	return false;
}

void Button::setTexture(const sf::Texture & ntexture, const sf::RenderWindow & window) {
	texture1 = ntexture;
	texture2 = ntexture;
}

void Button::setString(const std::string & ntext) {
	text.setString(ntext);
}

void Button::setPos(const glm::vec2 & pos, const sf::RenderWindow & window) {
	text.setPos(pos, window);
	GUIComponent::setPos(pos, window);
}

void Button::resetButton() {
	leftButton.resetTime();
	rightButton.resetTime();
}
