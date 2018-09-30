#include "WorldInfo.h"

#include "Entity/Player.h"
#include <fstream>

#include "Utils/Random.h"

WorldInfo::WorldInfo(const std::string& path) : path(path) {

	std::ifstream is("res/saves/" + path + "/info.world");

	if (!is.good()) {
		this->setPosition = true;
		this->seed = Rand::get().intInRange(321, 4332455);
		this->path = "newWorld";
	}
	else {
		std::string line;
		while (std::getline(is, line)) {
			if (line == "")
				continue;

			else if (line == "pos")
				is >> pos.x >> pos.y >> pos.z;

			else if (line == "Inventory") {

			}

			else if (line == "seed")
				is >> seed;
		}
	}

}

WorldInfo::~WorldInfo() {
}

bool WorldInfo::Save(Player& player) {
	std::ofstream os("res/saves/" + path + "/info.world", std::ofstream::out | std::ofstream::trunc);

	if (!os.good())
		return false;

	os << "pos\n" << player.getPos().x << " " << player.getPos().y << " " << player.getPos().z << "\n\n";

	os << "Inventory\n\n";

	Inventory* inventory = &player.getInventory();

	for (int i = 0; i < inventory->getInvSize(); i++) {

		Slot& slot = inventory->getComp(i).slot;

		switch (slot.type) {
		case SlotType::BLOCK:
			os << "b " << (int)slot.block->id << " " << slot.getStackSize() << "\n";
			break;
		case SlotType::MATERIAL:
			os << "m " << (int)slot.material->id << " " << slot.getStackSize() << "\n";
			break;
		case SlotType::ITEM:
			os << "i " << (int)slot.item->id << " " << slot.getStackSize() << "\n";
			break;
		case SlotType::NONE:
			os << "n 0 0\n";
			break;
		}
	}

	os << "\nseed\n" << seed << "\n\n";

	return true;
}
