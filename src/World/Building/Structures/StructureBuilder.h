#pragma once

#include "World/Chunk/Chunk.h"

class StructureBuilder {
public:
	StructureBuilder(Chunk* c);
	~StructureBuilder();

	void addBlock(int x, int y, int z, ID id);
	void addLayer(int sx, int sz, int ex, int ez, int y, ID id);
	void addLineX(int s, int e, int y, int z, ID id);
	void addLineZ(int s, int e, int x, int y, ID id);
	void addLineY(int s, int e, int x, int z, ID id);

private:
	Chunk* c;
};

