#pragma once

#include "../StateBase.h"
#include "GUI/Button.h"
#include "Utils/ToggleKey.h"

#include <memory>

class World;

class PauseMenu : public StateBase {
public:
	PauseMenu(Application& applic, World* world, StateBase* parent);
	~PauseMenu();

	void handleInput(float deltaTime, const Camera& camera) override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;
	void onResume() override;

private:
	std::vector<Button> buttons;
	ToggleKey escape;
	TextureComponent loading;
	World* world;
	bool returning = false;
};

