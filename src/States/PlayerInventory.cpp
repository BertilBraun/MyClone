#include "PlayerInventory.h"

#include "SFML/Graphics.hpp"
#include "Application.h"

PlayerInventory::PlayerInventory(Application & applic, Player* player) :
	StateBase(applic),
	invBackgound(glm::vec2(0.5f, 0.5f), glm::vec2(0.55f, 0.65f), "GUI/invBackground.png", (*app->getWindow())),
	selectedComp(glm::vec2(0.5f, 0.5f), glm::vec2(0.045, 0.06), (*app->getWindow())),
	player(player),
	craftingGrid(app, &player->getInventory())
{ }

PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::handleInput(float deltaTime, const Camera & camera)
{
}

void PlayerInventory::update(float deltaTime) {

	Inventory* inventory(&player->getInventory());

	for (unsigned int i = 0; i < (*inventory).getInvSize(); i++) {
		if ((*inventory).getComp(i).pressed()) {
			Slot& slot = (*inventory)[i];

			if (slot != Slot() && selectedComp.slot == Slot()) {
				selectedComp.setSlot(slot);
				inventory->resetSlot(i);
			}
			else if (slot == selectedComp.slot) {
				if (slot.type == SlotType::BLOCK)
					inventory->add(slot.block->id, slot.add(selectedComp.slot.getStackSize()));
				if (slot.type == SlotType::MATERIAL)
					inventory->add(slot.material->id, slot.add(selectedComp.slot.getStackSize()));
				if (slot.type == SlotType::ITEM)
					if (slot.add(selectedComp.slot.getStackSize()))
						inventory->add(slot.item->id);
				selectedComp.resetSlot();
				inventory->updateSlot(i);
			}
			else if (slot == Slot() && selectedComp.slot != Slot()) {
				inventory->setSlot(i, selectedComp.slot);
				selectedComp.resetSlot();
			}
			break;
		}
		else if ((*inventory).getComp(i).pressedR()) {
			
			Slot& slot = (*inventory)[i];

			if (selectedComp.slot == Slot()) {

				selectedComp.slot = slot;
				selectedComp.slot.setStackSize(1);
				selectedComp.update();

				slot.removeOne();
				if (!slot.getStackSize())
					slot = Slot();
				inventory->updateSlot(i);
			}
			else if (selectedComp.slot == slot) {
				if (!slot.add(1)) {
					selectedComp.resetSlot();
					inventory->updateSlot(i);
				}
			}
			break;
		}
	}

	if (selectedComp.slot != Slot()) {

		auto& window = (*app->getWindow());
		const auto& mPos = sf::Mouse::getPosition(window);
		glm::vec2 pos((float)mPos.x / (float)window.getSize().x, (float)mPos.y / (float)window.getSize().y);
		selectedComp.setPos(pos);
	}

	craftingGrid.update(selectedComp);
}

void PlayerInventory::render(MasterRenderer & renderer) {
	
	invBackgound.draw(renderer);

	Inventory* inventory(&player->getInventory());

	for (int i = 0; i < (*inventory).getInvSize(); i++)
		(*inventory).getComp(i).draw(renderer);
	
	craftingGrid.render(renderer);

	selectedComp.draw(renderer);
}

void PlayerInventory::onOpen() {

	const sf::RenderWindow& window = (*app->getWindow());
	sf::Mouse::setPosition(sf::Vector2i(sf::Vector2f(window.getSize()) / 2.0f), window);
	app->turnOnMouse();
}

void PlayerInventory::onResume() {
}
