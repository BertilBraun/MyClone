#pragma once
#include "../StateBase.h"
#include "GUI/Button.h"
#include "GUI/TextBox.h"
#include "Utils/ToggleKey.h"
#include <vector>

class MenuNewWorld : public StateBase {
public:
	MenuNewWorld(Application& applic);
	~MenuNewWorld();

	void handleInput(float deltaTime, const Camera& camera) override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;
	void onResume() override;

private:
	std::vector<Button> buttons;
	TextureComponent background;
	TextBox name, seed;
	bool writingToName = true;
	ToggleKey escape, enter;
};
