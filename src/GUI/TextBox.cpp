#include "TextBox.h"

TextBox::TextBox(const glm::vec2 & pos, const glm::vec2 & size, const std::string & texturepath, const sf::RenderWindow & window) :
	textComponent(pos, size, "", window),
	textureComponent(pos, size, texturepath, window)
{
	for (int i = 0; i < 26; i++)
		keys.emplace_back(ToggleKey(static_cast<sf::Keyboard::Key>(i), 0.15f));
}

void TextBox::Update() {
	for (int i = 0; i < 26; i++)
		if (keys[i].isKeyPressed()) {
			addCharToString((char)(i + 65));
			return;
		}
}

void TextBox::draw(MasterRenderer & renderer) {
	textureComponent.draw(renderer);
	textComponent.draw(renderer);
}

void TextBox::addCharToString(char c) {
	Text += c;
	textComponent.setString(Text);
}

std::string TextBox::getText() {
	return Text;
}
