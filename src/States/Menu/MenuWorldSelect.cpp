#include "MenuWorldSelect.h"

#include "Utils/ToggleKey.h"
#include "Application.h"
#include "../PlayingState.h"
#include "MenuNewWorld.h"
#include <fstream>

MenuWorldSelect::MenuWorldSelect(Application& applic) :
	StateBase(applic),
	escape(sf::Keyboard::Key::Escape, 0.2f),
	background(glm::vec2(0.5f, 0.5f), glm::vec2(1, 1), "GUI/dirtBackground.jpg", (*app->getWindow()))
{
	buttons.emplace_back(glm::vec2(0.8f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "PLAY", (*app->getWindow()), [&] {
		std::ifstream is(INFO_FILE_PATH);

		std::vector<std::string> line;
		int in;
		std::string l;
		is >> in;

		std::getline(is, l);

		for (int i = 0; i < in; i++) {
			std::getline(is, l);
			line.push_back(l);
		}

		if (in <= 0 || index >= in)
			return;

		app->pushState<StatePlaying>(*app, line[index]); 
	});

	std::ifstream is(INFO_FILE_PATH);
	int in;
	is >> in;

	buttons.emplace_back(glm::vec2(0.2f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "NEW WORLD", (*app->getWindow()), [&] { app->pushState<MenuNewWorld>(*app); });

	/*buttons.emplace_back(glm::vec2(0.5f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "Button", "DELETE", app->getWindow(), [&] { 
		std::ifstream is(INFO_FILE_PATH);

		std::vector<std::string> line;
		int in;
		std::string l;
		is >> in;

		if (in <= 0 || index >= in)
			return;

		std::getline(is, l);

		for (int i = 0; i < in; i++) {
			std::getline(is, l);
			line.push_back(l);
		}

		line.erase(line.begin() + index);

		std::ofstream os(INFO_FILE_PATH);

		os << index << "\n";
		for (int i = 0; i < index; i++)
			os << line[i] << "\n";

		buttons.erase(buttons.begin() + index--);
		onResume();  
	});*/
	
	is.close();
	is.open(INFO_FILE_PATH);
	std::string line;

	is >> in;

	for (int i = 0; i < in && i < 5; i++) {
		is >> line;
		buttons.emplace_back(glm::vec2(0.5f, 0.2f + i * 0.1f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", line, (*app->getWindow()));
	}	
}

MenuWorldSelect::~MenuWorldSelect()
{
}

void MenuWorldSelect::handleInput(float deltaTime, const Camera & camera)
{
}

void MenuWorldSelect::update(float deltaTime) {

	if (escape.isKeyPressed())
		app->popState();

	for (int i = 0; i < 2; i++)
		buttons[i].pressed((*app->getWindow()));

	for (int i = 2; i < buttons.size(); i++) {
		Button& button = buttons[i];

		if (button.pressed((*app->getWindow()))) {
			index = i - 2;
			std::cout << index << "index " << i << "i\n";
		}
	}
}

void MenuWorldSelect::render(MasterRenderer & renderer) {

	background.draw(renderer);

	for (Button& button : buttons)
		button.draw(renderer);
}

void MenuWorldSelect::onOpen() {
}

void MenuWorldSelect::onResume() {
	buttons.clear();
	buttons.emplace_back(glm::vec2(0.8f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "PLAY", (*app->getWindow()), [&] {
		std::ifstream is(INFO_FILE_PATH);

		std::vector<std::string> line;
		int in;
		std::string l;
		is >> in;

		std::getline(is, l);

		for (int i = 0; i < in; i++) {
			std::getline(is, l);
			line.push_back(l);
		}

		if (in <= 0 || index >= in)
			return;

		app->pushState<StatePlaying>(*app, line[index]);
	});

	std::ifstream is(INFO_FILE_PATH);
	int in;
	is >> in;
	buttons.emplace_back(glm::vec2(0.2f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "HoverButton", "NEW WORLD", (*app->getWindow()), [&] { app->pushState<MenuNewWorld>(*app); });
	/*buttons.emplace_back(glm::vec2(0.5f, 0.7f), glm::vec2(0.2f, 0.065f), "Button", "Button", "DELETE", app->getWindow(), [&] {
		std::ifstream is(INFO_FILE_PATH);

		std::vector<std::string> line;
		int in;
		std::string l;
		is >> in;

		if (in <= 0 || index >= in)
			return;

		std::getline(is, l);

		for (int i = 0; i < in; i++) {
			std::getline(is, l);
			line.push_back(l);
		}

		line.erase(line.begin() + index);

		std::ofstream os(INFO_FILE_PATH);

		os << index << "\n";
		for (int i = 0; i < index; i++)
			os << line[i] << "\n";

		buttons.erase(buttons.begin() + index--);
		onResume();
	});*/

	is.close();
	is.open(INFO_FILE_PATH);
	std::string line;

	is >> in;

	for (int i = 0; i < in && i < 5; i++) {
		is >> line;
		buttons.emplace_back(glm::vec2(0.5f, 0.2f + i * 0.1f), glm::vec2(0.2f, 0.065f), "Button", "Button", line, (*app->getWindow()));
	}
}
