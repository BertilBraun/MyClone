#include "Application.h"

#include <exception>

#include "States/Menu/MainMenu.h"

#include "DataBase/DataBase.h"
#include "Texture/TextureAtlas.h"
#include "Math/NoiseGenerator.h"
#include "Utils/FPSCounter.h"

#include "defines.h"

Application::Application()
:   context()
,	camera(this)
,	masterRenderer(camera.getProjMat())
{
	TextureAtlas::get();
	Loader::get();
	DataBase::get(this);

	pushState<MainMenu>(*this);
}


void Application::runLoop() {
	sf::Clock Timer;
	FPSCounter FPSCount;

	while (getWindow()->isOpen() && !states.empty()) {

		float deltaTime = std::min(Timer.restart().asSeconds(), 0.15f);

		auto& state = *states.top();

		camera.Update(context.window, state.shouldUpdateCamera());
		FPSCount.update();

		state.handleInput(deltaTime, camera);
		state.update(deltaTime);
		state.render(masterRenderer);
		masterRenderer.ProcessSFML(FPSCount.getText());

		masterRenderer.Render(context.window, camera, deltaTime);

		handleEvents();

		if (isPopState) {
			isPopState = false;
			states.pop();
			if (!states.empty())
				states.top()->onResume();
		}

		if (shouldReturnToMainMenu) {
			shouldReturnToMainMenu = false;
			for (int i = 0; i <= states.size(); i++)
				states.pop();
			if (!states.empty())
				states.top()->onResume();
		}
	}
}

void Application::handleEvents() {
	sf::Event e;
	while (context.window.pollEvent(e))
		if (e.type == sf::Event::Closed)
			context.window.close();

	context.window.display();
}


void Application::popState() {
	isPopState = true;
}

void Application::returnToMainMenu() {
	shouldReturnToMainMenu = true;
}

void Application::turnOffMouse() {
	context.window.setMouseCursorVisible(false);
}

void Application::turnOnMouse() {
	context.window.setMouseCursorVisible(true);
}

Camera& Application::getCamera() {
	return camera;
}

sf::RenderWindow * Application::getWindow() {
	return &context.window;
}
