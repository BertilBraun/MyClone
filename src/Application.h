#pragma once
#include <stack>
#include <memory>

#include "States/StateBase.h"
#include "Renderer/MasterRenderer.h"

#include "Extern/Context.h"
#include "Entity/Camera.h"

class Application {
public:
	Application();

	void runLoop();

	template<typename T, typename... Args>
	void pushState(Args&&... args) {
		states.emplace(std::make_unique<T>(std::forward<Args>(args)...));
		states.top()->onOpen();
	}

	void popState();
	void returnToMainMenu();

	void turnOffMouse();
	void turnOnMouse ();

	Camera& getCamera();
	sf::RenderWindow* getWindow();

private:
	void handleEvents();

	std::stack<std::unique_ptr<StateBase>> states;

	Context context;
	Camera camera;
	MasterRenderer masterRenderer;
	bool isPopState = false, shouldReturnToMainMenu = false;
};
