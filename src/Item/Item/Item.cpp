#include "Item.h"
#include <fstream>

Item::Item(const std::string & path) :
	name(path)
{
	std::ifstream inFile("Res/Infos/Items/" + path + ".item");

	if (!inFile.is_open())
		throw std::runtime_error("Unable to open item file: " + path + "!");

	std::string line;
	while (std::getline(inFile, line)) {
		if (line == "id") {
			int i;
			inFile >> i;
			id = static_cast<ItID>(i);
		}
		else if (line == "invTexture") {
			int x, y;
			inFile >> x >> y;
			invTexture = { x, y };
		}
		else if (line == "breakMultiplier") {
			inFile >> breakMultiplier;
		}
		else if (line == "attackValue") {
			inFile >> attackValue;
		}
		else if (line == "hp") {
			inFile >> hp;
		}
	}
}

Item::Item(ItID id, float breakMultiplier, unsigned int attackValue, int hp):
	id(id),
	breakMultiplier(breakMultiplier),
	attackValue(attackValue),
	hp(hp)
{ }
