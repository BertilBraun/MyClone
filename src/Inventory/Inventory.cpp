#include "Inventory.h"

#include <fstream>

#include "Renderer/MasterRenderer.h"
#include "Application.h"

Inventory::Inventory(Application* app, const std::string& path, int INV_SIZE, int INV_DISPLAY_SIZE) :
	app(app),
	INV_SIZE(INV_SIZE),
	INV_DISPLAY_SIZE(INV_DISPLAY_SIZE),
	hotbar(glm::vec2(0.5, 0.925), glm::vec2(0.5, 0.075), "GUI/hotbar.png", (*app->getWindow())),
	selectedSlot(glm::vec2(0.5, 0.925), glm::vec2(0.055, 0.075), "GUI/selctedSlot.png", (*app->getWindow()))
{ 
	comp.reserve(INV_SIZE);

	for (int i = 0; i < INV_SIZE; i++)
		comp.emplace_back(	glm::vec2(0.274 + (i % INV_DISPLAY_SIZE) * 0.0563, 0.76 - (float)((int)(i / INV_DISPLAY_SIZE)) * 0.068 - ((int)(i / INV_DISPLAY_SIZE) > 0 ? 0.0195 : 0)),
							glm::vec2(0.045, 0.06), (*app->getWindow()));

	dispComp.reserve(INV_SIZE);

	for (int i = 0; i < INV_DISPLAY_SIZE; i++)
		dispComp.emplace_back(glm::vec2(0.274 + i * 0.0563, 0.925),	glm::vec2(0.045, 0.06), (*app->getWindow()));

	if (!load(path)) {
		add(ItID::AXE);
		add(ID::Plank, 64);
		add(MID::IRON, 64);
	}
}


Inventory::~Inventory()
{
}

bool Inventory::add(Slot & s) {

	if (s.type == SlotType::BLOCK			&& s.block->id != ID::Air)
		return add(s.block->id, s.getStackSize());

	else if (s.type == SlotType::MATERIAL	&& s.material->id != MID::NONE)
		return add(s.material->id, s.getStackSize());

	else if (s.type == SlotType::ITEM		&& s.item->id != ItID::NONE)
		return add(s.item->id);

	return false;
}

bool Inventory::add(ItID id) {

	for (int i = 0; i < INV_SIZE; i++) 
		if (comp[i].slot.type == SlotType::NONE) {

			setSlot(i, Slot(id));
			return false;
		}

	return true;
}

int Inventory::add(ID id, int ammount) {

	if (ammount == 0)
		return 0;

	for (int i = 0; i < INV_SIZE; i++) {
		Slot& slot = comp[i].slot;
		if (slot.type == SlotType::BLOCK &&	id == slot.block->id && slot.getStackSize() < slot.getMaxStackSize()) {

			int value = slot.add(ammount);
			if (i < INV_DISPLAY_SIZE)
				dispComp[i].slot.add(ammount);

			updateSlot(i);
			return add(id, value);
		}
	}

	for (int i = 0; i < INV_SIZE; i++) {
		Slot& slot = comp[i].slot;
		if (slot.type == SlotType::NONE) {

			setSlot(i, Slot(id, ammount));
			return add(id, std::max(ammount - comp[i].slot.getMaxStackSize(), 0));
		}
	}

	return ammount;
}

int Inventory::add(MID id, int ammount) {

	if (ammount == 0)
		return 0;

	for (int i = 0; i < INV_SIZE; i++) {
		Slot& slot = comp[i].slot;
		if (slot.type == SlotType::MATERIAL && id == slot.material->id && slot.getStackSize() < slot.getMaxStackSize()) {

			int value = slot.add(ammount);
			if (i < INV_DISPLAY_SIZE)
				dispComp[i].slot.add(ammount);
			updateSlot(i);
			return add(id, value);
		}
	}

	for (int i = 0; i < INV_SIZE; i++) {
		Slot& slot = comp[i].slot;
		if ((slot.type == SlotType::MATERIAL && slot.material->id == MID::NONE) ||
			slot.type == SlotType::NONE) {

			Slot s(id, 0);
			int value = s.add(ammount);

			setSlot(i, s);
			return add(id, value);
		}
	}
	return ammount;
}

void Inventory::render(MasterRenderer & renderer) {

	hotbar.draw(renderer);
	selectedSlot.draw(renderer);

	for (int i = 0; i < INV_DISPLAY_SIZE; i++)
		dispComp[i].draw(renderer);
}

void Inventory::Update() {

	static ToggleKey up(sf::Keyboard::Up);
	static ToggleKey down(sf::Keyboard::Down);
	static ToggleKey q(sf::Keyboard::Q);
	static std::vector<ToggleKey> numKeys{
		ToggleKey(sf::Keyboard::Num1),
		ToggleKey(sf::Keyboard::Num2),
		ToggleKey(sf::Keyboard::Num3),
		ToggleKey(sf::Keyboard::Num4),
		ToggleKey(sf::Keyboard::Num5),
		ToggleKey(sf::Keyboard::Num6),
		ToggleKey(sf::Keyboard::Num7),
		ToggleKey(sf::Keyboard::Num8),
		ToggleKey(sf::Keyboard::Num9)
	};

	if (up.isKeyPressed())
		currentSlot = std::max(--currentSlot, 0);

	if (down.isKeyPressed())
		currentSlot = std::min(++currentSlot, INV_DISPLAY_SIZE - 1);

	for (int i = 0; i < numKeys.size(); i++)
		if (numKeys[i].isKeyPressed()) {
			currentSlot = i;
			break;
		}

	sf::Event e;
	while (app->getWindow()->pollEvent(e)) 
		if (e.type == sf::Event::MouseWheelMoved) {
			if (e.mouseWheel.delta * 1000 > 0)
				currentSlot = std::max(--currentSlot, 0);
			else if (e.mouseWheel.delta * 1000 < 0)
				currentSlot = std::min(++currentSlot, INV_DISPLAY_SIZE - 1);
		}
	
	if (q.isKeyPressed())
		resetSlot(currentSlot);

	selectedSlot.setPos(glm::vec2(0.275 + currentSlot * 0.056, 0.925), *app->getWindow());
}

bool Inventory::tryToRemove(ItID id) {
	
	if (comp[currentSlot].slot.type == SlotType::ITEM && comp[currentSlot].slot.item->id == id) {
		resetSlot(currentSlot);
		return true;
	}

	for (int i = 0; i < INV_SIZE; i++) {
		Slot& slot = comp[i].slot;
		if (slot.type == SlotType::ITEM && slot.item->id == id) {
			resetSlot(i);
			return true;
		}
	}
	
	return false;
}

int Inventory::tryToRemove(ID id, int ammount) {

	if (ammount == 0)
		return 0;

	int index = 0;

	if (comp[currentSlot].slot.type == SlotType::BLOCK && comp[currentSlot].slot.block->id == id) 
		index = currentSlot;	
	else {
		for (; index < comp.size(); index++)
			if (comp[index].slot.type == SlotType::BLOCK && comp[index].slot.block->id == id)
				break;

		if (comp[index].slot.type != SlotType::BLOCK || comp[index].slot.block->id != id)
			return ammount;
	}
	Slot s = comp[index].slot;

	for (int i = 0; i < ammount; i++) 
		if (!s.removeOne()) {
			resetSlot(index);
			return tryToRemove(id, i);
		}

	setSlot(index, s);

	return 0;
}

int Inventory::tryToRemove(MID id, int ammount) {

	if (ammount == 0)
		return 0;

	int index = 0;

	if (comp[currentSlot].slot.type == SlotType::MATERIAL && comp[currentSlot].slot.material->id == id)
		index = currentSlot;
	else {
		for (; index < comp.size(); index++)
			if (comp[index].slot.type == SlotType::MATERIAL && comp[index].slot.material->id == id)
				break;

		if (comp[index].slot.type != SlotType::MATERIAL || comp[index].slot.material->id != id)
			return ammount;
	}
	Slot s = comp[index].slot;

	for (int i = 0; i < ammount; i++)
		if (!s.removeOne()) {
			resetSlot(index);
			return tryToRemove(id, i);
		}

	setSlot(index, s);

	return 0;
}

Slot & Inventory::currSlot() {
	return comp[currentSlot].slot;
}

Slot & Inventory::operator[](int i) {
	
	return comp[i].slot;
}

int Inventory::getInvSize() {
	return INV_SIZE;
}

Component & Inventory::getComp(int i) {
	return comp[i];
}

void Inventory::resetSlot(int i) {
	comp[i].resetSlot();
	if (i < INV_DISPLAY_SIZE)
		dispComp[i].resetSlot();
}

void Inventory::setSlot(int i, const Slot & s) {
	comp[i].setSlot(s);
	if (i < INV_DISPLAY_SIZE)
		dispComp[i].setSlot(s);
}

void Inventory::updateSlot(int i) {
	comp[i].update();
	if (i < INV_DISPLAY_SIZE)
		dispComp[i].update();
}

bool Inventory::load(const std::string & path) {

	std::ifstream is("res/saves/" + path + "/info.world");

	if (!is.good()) {
		std::cout << "DIDNT LOAD INVENTORY SUCESSFULLY\n";
		return false;
	}
	else {
		std::string line;
		while (std::getline(is, line)) 
			if (line == "Inventory") {

				int id, a;
				char c;

				for (int i = 0; i < INV_SIZE; i++) {

					is >> c >> id >> a;

					switch (c) {
					case 'b':
						setSlot(i, Slot(static_cast<ID>(id), a));
						break;
					case 'm':
						setSlot(i, Slot(static_cast<MID>(id), a));
						break;
					case 'i':
						setSlot(i, Slot(static_cast<ItID>(id)));
						break;
					case 'n':
						setSlot(i, Slot());
						break;
					}
				}


			}
	}
	return true;
}

int Inventory::getCurrentSlot() {
	return currentSlot;
}
