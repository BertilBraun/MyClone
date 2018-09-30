#include "Block.h"

#include <fstream>
#include <iostream>

Block::Block(const std::string& path) :
	name(path)
{
	std::ifstream inFile("Res/Infos/Blocks/" + path + ".block");

	if (!inFile.is_open()) 
		throw std::runtime_error("Unable to open block file: " + path + "!");

	std::string line;
	while (std::getline(inFile, line)) {
		if (line == "")
			continue;
		else if (line == "TexTop") {
			int x, y;
			inFile >> x >> y;
			textureUp = { x, y };
		}
		else if (line == "TexSide") {
			int x, y;
			inFile >> x >> y;
			textureSide = { x, y };
		}
		else if (line == "TexBottom") {
			int x, y;
			inFile >> x >> y;
			textureDown = { x, y };
		}
		else if (line == "TexAll") {
			int x, y;
			inFile >> x >> y;
			textureUp = { x, y };
			textureSide = { x, y };
			textureDown = { x, y };
		}
		else if (line == "Id") {
			int nid;
			inFile >> nid;
			id = static_cast<ID>(nid);
		}
		else if (line == "Opaque") {
			inFile >> opaque;
		}
		else if (line == "Solid") {
			inFile >> solid;
		}
		else if (line == "BlockType") {
			int id;
			inFile >> id;
			blockType = static_cast<BlockType>(id);
		}
		else if (line == "MeshType") {
			int id;
			inFile >> id;
			meshType = static_cast<MeshType>(id);
		}
		else if (line == "AABBDim") {
			int x = 1, y = 1, z = 1;
			inFile >> x >> y >> z;
			aabb.SetDim({ x, y, z });
		}
		else if (line == "stackSize") {
			inFile >> stackSize;
		}
		else if (line == "luminationFactor") {
			inFile >> luminationFactor;
		}
		else if (line == "breakTime") {
			inFile >> breakTime;
		}
		else if (line == "demageOnHit") {
			inFile >> demageOnHit;
		}
		else if (line == "blastResistance") {
			inFile >> blastResistance;
		}
		else if (line == "drop") {
			inFile >> dc >> did >> da;
		}
	}
}

void Block::Init() {
	switch (dc) {
	case 'b':
		drop = Slot(static_cast<ID>(did), da);
		break;
	case 'm':
		drop = Slot(static_cast<MID>(did), da);
		break;
	case 'i':
		drop = Slot(static_cast<ItID>(did));
		break;
	}

	if (drop == Slot())
		drop = Slot(id, 1);
}
