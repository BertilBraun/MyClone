#include "MenuNewWorld.h"

#include "Utils/ToggleKey.h"
#include "Application.h"
#include "../PlayingState.h"

#include <Windows.h>

MenuNewWorld::MenuNewWorld(Application& applic) :
	StateBase(applic),
	escape(sf::Keyboard::Key::Escape, 0.2f),
	enter(sf::Keyboard::Key::Enter, 0.2f),
	background(glm::vec2(0.5f, 0.5f), glm::vec2(1, 1), "GUI/dirtBackground.jpg", (*app->getWindow())),
	name(glm::vec2(0.5f, 0.4f), glm::vec2(0.3f, 0.065f), "Button", (*app->getWindow())),
	seed(glm::vec2(0.5f, 0.5f), glm::vec2(0.3f, 0.065f), "Button", (*app->getWindow()))
{
	buttons.emplace_back(glm::vec2(0.7f, 0.7f), glm::vec2(0.3f, 0.065f), "Button", "HoverButton", "CREATE", (*app->getWindow()), [&] {
		/*std::string path = "res/saves/" + name.getText();

		DWORD attribs = GetFileAttributesA(path.c_str());
		if (!attribs == INVALID_FILE_ATTRIBUTES || (attribs & FILE_ATTRIBUTE_DIRECTORY)) {

			CreateDirectory(path.c_str(), NULL);
			CreateDirectory(std::string(path + "/chunks").c_str(), NULL);

			std::ofstream os(std::string(path + "/info.world"));

			if (!seed.getText().empty())
				os << "seed\n" << seed.getText();
			else
				os << "seed\n" << rand();

			os.close();
			std::ifstream is(INFO_FILE_PATH);

			std::vector<std::string> line;
			int index;
			std::string l; 
			std::getline(is, l);

			index = std::stoi(l);

			for (int i = 0; i < index; i++) {
				std::getline(is, l);
				line.push_back(l);
			}

			is.close();
			os.open(INFO_FILE_PATH);

			os << index + 1 << "\n";
			for (int i = 0; i < index; i++)
				os << line[i] << "\n";
			os << name.getText();
		}*/

		app->popState();
	});
	//buttons.emplace_back(glm::vec2(0.3f, 0.7f), glm::vec2(0.3f, 0.065f), "Button", "Button", "NEW WORLD", app->getWindow(), [&] {});
	//buttons.emplace_back(glm::vec2(0.5f, 0.6f), glm::vec2(0.2f, 0.065f), "Button", "Button", "QUIT",		app->getWindow(), [&] { app->popState(); });
}

MenuNewWorld::~MenuNewWorld()
{
}

void MenuNewWorld::handleInput(float deltaTime, const Camera & camera)
{
}

void MenuNewWorld::update(float deltaTime) {

	if (escape.isKeyPressed())
		app->popState();

	if (enter.isKeyPressed())
		writingToName = !writingToName;

	for (Button& button : buttons)
		button.pressed((*app->getWindow()));

	if (writingToName)
		name.Update();
	else
		seed.Update();
}

void MenuNewWorld::render(MasterRenderer & renderer) {

	background.draw(renderer);

	for (Button& button : buttons)
		button.draw(renderer);

	name.draw(renderer);
	seed.draw(renderer);
}

void MenuNewWorld::onOpen() {
}

void MenuNewWorld::onResume() {
	for (Button& button : buttons)
		button.resetButton();
}
