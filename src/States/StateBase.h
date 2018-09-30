#pragma once

#include "SFML/Window.hpp"

class MasterRenderer;
class Application;
class World;
class Camera;

class StateBase {
public:
	StateBase(Application& app)
	: app(&app)
	{ }

	virtual ~StateBase()  = default;

	virtual void handleInput(float deltaTime, const Camera& camera) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(MasterRenderer& renderer) = 0;
	virtual void onOpen() = 0;
	virtual void onResume() = 0;

	bool shouldUpdateCamera() {
		return updateCamera;
	}

protected:
	Application* app;
	bool updateCamera = false;
};

