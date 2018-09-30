#include "PlayingState.h"

#include "Menu/PauseMenu.h"

#include "defines.h"
#include "Loader/Loader.h"
#include "Texture/TextureAtlas.h"
#include "Utils/Mutexes.h"

#include "Inventory/Crafting/Recepies.h"

StatePlaying::StatePlaying(Application& applic, const std::string& path) :
	StateBase(applic),
	escape(sf::Keyboard::Key::Escape, 0.2f),
	inventory(sf::Keyboard::Key::E, 0.2f),
	craft(sf::Keyboard::Key::C, 0.2f),
	worldInfo(path),
	world(&player, &app->getCamera(), worldInfo),
	player(worldInfo, &world, app),
	crosshair(glm::vec2(0.5f, 0.5f), glm::vec2(0.015f, 0.02f), "Others/Crosshair.png", (*app->getWindow())),
	invState(*app, &player),
	craftState(*app, &player)
{
	app->getCamera().HookEntity(&player);
	Mutexes::get().mutex.unlock();
}

StatePlaying::~StatePlaying() {
	app->getCamera().unHook();
	worldInfo.Save(player);
}

void StatePlaying::handleInput(float deltaTime, const Camera& camera) {
	TRY(
		if (state == PlayStates::NONE) {
			player.KeyboardInput(camera);

			if (escape.isKeyPressed())
				app->pushState<PauseMenu>(*app, &world);

			else if (inventory.isKeyPressed()) {
				state = PlayStates::INVENTORY;
				updateCamera = false;
				invState.onOpen();
			}
			else if (craft.isKeyPressed()) {
				state = PlayStates::CRAFTING;
				updateCamera = false;
				craftState.onOpen();
			}
		}
		else if (escape.isKeyPressed() || inventory.isKeyPressed()) {
			state = PlayStates::NONE;
			onResume();
		}
		
	);
}

void StatePlaying::update(float deltaTime) {

	TRY(
		player.Update(deltaTime, &world);

		if (state == PlayStates::NONE)
			world.Update(deltaTime);

		if (state == PlayStates::INVENTORY)
			invState.update(deltaTime);
		if (state == PlayStates::CRAFTING)
			craftState.update(deltaTime);
	);
}

void StatePlaying::render(MasterRenderer& renderer) {
	TRY(
		renderer.RenderSkybox();
		world.Render(renderer);
		player.DisplayInformation(renderer, app->getCamera(), app);
		
		if (state == PlayStates::NONE)
			crosshair.draw(renderer);
		else if (state == PlayStates::INVENTORY)
			invState.render(renderer);
		else if (state == PlayStates::CRAFTING)
			craftState.render(renderer);
	);
}

void StatePlaying::onOpen() {
	sf::Mouse::setPosition(sf::Vector2i(400, 400), (*app->getWindow()));
	app->turnOffMouse();
	updateCamera = true;
}

void StatePlaying::onResume() {
	sf::Mouse::setPosition(sf::Vector2i(400, 400), (*app->getWindow()));
	app->turnOffMouse();
	updateCamera = true;

	escape.resetTime();
	inventory.resetTime();
}
