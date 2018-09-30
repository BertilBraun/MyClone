#pragma once

enum class ID : char {

	Air = 0,
	Grass,
	Dirt,
	Stone,
	Wood,
	Leave,
	Sand,
	Cobble,
	Water,
	Cactus,
	Gravel,
	ShortGrass,
	Rose,
	DeadBush,
	Plank,
	Iron,
	SnowGrass,
	Fern,
	PineWood,
	PineLeave,
	Glass,

	NUM
};

enum class MID : char {

	NONE,
	COAL,
	IRON,
	DIAMOND,

	NUM
};

enum class ItID : char {

	NONE,
	AXE,

	NUM
};

enum class MeshType : short {

	BLOCK,
	X,
	HALF,
	CACTUS,

	NUM
};

enum class BlockType : short {

	SOLID,
	FLUID,
	LEAVE,

	NUM

};