#include "StructureBuilder.h"



StructureBuilder::StructureBuilder(Chunk* c) :
	c(c)
{ }


StructureBuilder::~StructureBuilder()
{
}

void StructureBuilder::addBlock(int x, int y, int z, ID id) {
	if (c->getBlock(x, y, z).id == ID::Air || c->getBlock(x, y, z).getData().blockType != BlockType::SOLID)
		c->setBlock(x, y, z, id);
}

void StructureBuilder::addLayer(int sx, int sz, int ex, int ez, int y, ID id) {
	for (int x = sx; x <= ex; x++)
		for (int z = sz; z <= ez; z++)
			addBlock(x, y, z, id);
}

void StructureBuilder::addLineX(int s, int e, int y, int z, ID id) {
	for (int x = s; x <= e; x++)
		addBlock(x, y, z, id);
}

void StructureBuilder::addLineZ(int s, int e, int x, int y, ID id) {
	for (int z = s; z <= e; z++)
		addBlock(x, y, z, id);
}

void StructureBuilder::addLineY(int s, int e, int x, int z, ID id) {
	for (int y = s; y <= e; y++)
		addBlock(x, y, z, id);
}
