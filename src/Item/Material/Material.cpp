#include "Material.h"

#include <fstream>


Material::Material(const std::string & path) :
	name(path)
{
	std::ifstream inFile("Res/Infos/Materials/" + path + ".material");

	if (!inFile.is_open())
		throw std::runtime_error("Unable to open material file: " + path + "!");

	std::string line;
	while (std::getline(inFile, line)) {
		if (line == "id") {
			int i;
			inFile >> i;
			id = static_cast<MID>(i);
		}
		else if (line == "invTexture") {
			int x, y;
			inFile >> x >> y;
			invTexture = { x, y };
		}
		else if (line == "stackSize") {
			inFile >> stackSize;
		}
	}
}
