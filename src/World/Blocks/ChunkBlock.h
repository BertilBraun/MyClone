#pragma once

#include "DataBase/DataBase.h"
#include "DataBase/ID.h"

#include <iostream>

class ChunkBlock {
public:
	ChunkBlock() : id(ID::Air) { }
	ChunkBlock(ID nid) :
		id(DataBase::get().getBlock(nid).id)
	{ }

	Block& getData() {
		return DataBase::get().getBlock(id);
	}

	inline int getSunlight() {
		return (light >> 4) & 0xF;
	}

	inline void setSunlight(int val) {
		light = (light & 0xF) | (val << 4);
	}

	inline int getTorchlight() {
		return light & 0xF;
	}

	inline void setTorchlight(int val) {
		light = (light & 0xF0) | val;
	}
	
	unsigned short light = 0;
	ID id;
};