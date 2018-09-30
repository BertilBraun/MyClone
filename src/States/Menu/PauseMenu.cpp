#include "PauseMenu.h"

#include "Utils/ToggleKey.h"
#include "Application.h"
#include "World/World.h"

PauseMenu::PauseMenu(Application& applic, World* world) :
	StateBase(applic),
	escape(sf::Keyboard::Key::Escape, 0.2f),
	background(glm::vec2(0.5f, 0.5f), glm::vec2(1, 1), "GUI/background.jpg", (*app->getWindow())),
	loading(glm::vec2(0.5f, 0.5f), glm::vec2(1, 1), "GUI/dirtBackground.jpg", (*app->getWindow())),
	world(world)
{ 
	buttons.emplace_back(glm::vec2(0.5f, 0.4f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "RESUME",			(*app->getWindow()), [&] { app->popState(); });
	buttons.emplace_back(glm::vec2(0.5f, 0.5f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "OPTIONS NA",		(*app->getWindow()));
	buttons.emplace_back(glm::vec2(0.5f, 0.6f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "SAVE", (*app->getWindow()), [&] { this->world->saveAll(); });
	buttons.emplace_back(glm::vec2(0.5f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "RETURN TO MENU", (*app->getWindow()), [&] { returning = true;  app->returnToMainMenu(); });
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::handleInput(float deltaTime, const Camera & camera)
{
}

void PauseMenu::update(float deltaTime) {
	
	if (escape.isKeyPressed())
		app->popState();

	for(Button& button : buttons)
		button.pressed((*app->getWindow()));
}

void PauseMenu::render(MasterRenderer & renderer) {

	background.draw(renderer);

	for (Button& button : buttons)
		button.draw(renderer);

	if (returning)
		loading.draw(renderer);
}

void PauseMenu::onOpen() {
	const sf::RenderWindow& window = (*app->getWindow());
	sf::Mouse::setPosition(sf::Vector2i(sf::Vector2f(window.getSize()) / 2.0f), window);
	app->turnOnMouse();
	updateCamera = false;
}

void PauseMenu::onResume() {

}
