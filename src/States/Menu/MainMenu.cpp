#include "MainMenu.h"

#include "Utils/ToggleKey.h"
#include "Application.h"
#include "MenuWorldSelect.h"

MainMenu::MainMenu(Application& applic) :
	StateBase(applic),
	background(glm::vec2(0.5f, 0.5f), glm::vec2(1, 1), "GUI/background.jpg", (*app->getWindow()))
{
	buttons.emplace_back(glm::vec2(0.5f, 0.4f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "PLAY", (*app->getWindow()), [&] { app->pushState<MenuWorldSelect>(*app); });
	buttons.emplace_back(glm::vec2(0.5f, 0.5f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "OPTIONS NA", (*app->getWindow()));
	buttons.emplace_back(glm::vec2(0.5f, 0.6f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "QUIT", (*app->getWindow()), [&] { app->popState(); });
}

MainMenu::~MainMenu()
{
}

void MainMenu::handleInput(float deltaTime, const Camera & camera)
{
}

void MainMenu::update(float deltaTime) {

	for (Button& button : buttons)
		button.pressed((*app->getWindow()));
}

void MainMenu::render(MasterRenderer & renderer) {

	background.draw(renderer);

	for (Button& button : buttons)
		button.draw(renderer);
}

void MainMenu::onOpen() {
	const sf::RenderWindow& window = (*app->getWindow());
	sf::Mouse::setPosition(sf::Vector2i(sf::Vector2f(window.getSize()) / 2.0f), window);
	app->turnOnMouse();
	updateCamera = false;
}

void MainMenu::onResume() {
	app->turnOnMouse();
	updateCamera = false;
	for (Button& button : buttons)
		button.resetButton();
}
