#pragma once
#include "../StateBase.h"
#include "GUI/Button.h"
#include "Utils/ToggleKey.h"

class MenuWorldSelect : public StateBase {
public:
	MenuWorldSelect(Application& applic);
	~MenuWorldSelect();

	void handleInput(float deltaTime, const Camera& camera) override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;
	void onResume() override;

private:
	std::vector<Button> buttons;
	TextureComponent background;
	ToggleKey escape;
	int index = 0;
};
