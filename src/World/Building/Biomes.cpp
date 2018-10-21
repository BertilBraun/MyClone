#include "Biomes.h"

#include "Utils/Random.h"
#include "Structures/StructureBuilder.h"

namespace Biome {

	Desert::Desert(int seed) :
		Biome(seed, 200, 100)
	{ 
		name = "Desert";
	}

	ChunkBlock Desert::getBeachBlock() {
		return ID::Sand;
	}

	ChunkBlock Desert::getUnderwaterBlock() {
		return Rand::get().intInRange(0, 10) < 3 ? ID::Gravel : ID::Sand;
	}

	ChunkBlock Desert::getUnderEarth()
	{
		return ID::Stone;
		return Rand::get().intInRange(0, 10) < 3 ? ID::Stone : ID::Cobble;
	}

	ChunkBlock Desert::getTopBlock() {
		return ID::Sand;
	}

	ChunkBlock Desert::getPlant() {

		return ID::DeadBush;
	}

	void Desert::addTree(int x, int y, int z, Chunk* c) {

		StructureBuilder builder(c);

		int ny = y + Rand::get().intInRange(3, 4);

		builder.addLineY(y, ny, x, z, ID::Cactus);
	}

	Grass::Grass(int seed) :
		Biome(seed, 10000, 5)
	{
		name = "Grass"; 
	}

	ChunkBlock Grass::getBeachBlock() {
		return ID::Sand;
	}

	ChunkBlock Grass::getUnderwaterBlock() {
		return Rand::get().intInRange(0, 10) < 3 ? ID::Gravel : ID::Sand;
	}

	ChunkBlock Grass::getUnderEarth()
	{
		if (!Rand::get().intInRange(0, 5))
			return ID::Iron;

		return ID::Stone;
	}

	ChunkBlock Grass::getTopBlock() {
		return ID::Grass;
	}

	ChunkBlock Grass::getPlant() {

		return Rand::get().intInRange(0, 20) < 1 ? ID::Rose : ID::ShortGrass;
	}

	Forest::Forest(int seed) :
		Biome(seed, 150, 10)
	{ 
		name = "Forest";
	}

	ChunkBlock Forest::getBeachBlock() {
		return ID::Sand;
	}

	ChunkBlock Forest::getUnderwaterBlock() {
		return Rand::get().intInRange(0, 10) < 3 ? ID::Gravel : ID::Sand;
	}

	ChunkBlock Forest::getUnderEarth()
	{
		if (!Rand::get().intInRange(0, 5))
			return ID::Iron;

		return ID::Stone;
	}

	ChunkBlock Forest::getTopBlock() {
		return ID::Grass;
	}

	ChunkBlock Forest::getPlant() {

		return Rand::get().intInRange(0, 20) < 1 ? ID::Rose : ID::ShortGrass;
	}

	SnowForest::SnowForest(int seed) :
		Biome(seed, 150, 10)
	{
		name = "SnowForest";
	}

	ChunkBlock SnowForest::getBeachBlock() {
		return ID::Sand;
	}

	ChunkBlock SnowForest::getUnderwaterBlock() {
		return Rand::get().intInRange(0, 10) < 3 ? ID::Gravel : ID::Sand;
	}

	ChunkBlock SnowForest::getUnderEarth()
	{
		if (!Rand::get().intInRange(0, 5))
			return ID::Iron;

		return ID::Stone;
	}

	ChunkBlock SnowForest::getTopBlock() {
		return ID::SnowGrass;
	}

	ChunkBlock SnowForest::getPlant() {

		return ID::Fern;
	}

	void SnowForest::addTree(int x, int y, int z, Chunk* c) {

		StructureBuilder builder(c);

		int ny = y + Rand::get().intInRange(2, 3);

		builder.addLayer(x - 2, z - 1, x + 2, z + 1, ny, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny, z + 2, ID::PineLeave);
		builder.addLineX(x - 1, x + 1, ny, z - 2, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny + 1, z, ID::PineLeave);
		builder.addLineZ(z - 1, z + 1, x, ny + 1, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny + 2, z + 1, ID::PineLeave);
		builder.addLineX(x - 1, x + 1, ny + 2, z - 1, ID::PineLeave);

		builder.addLayer(x - 1, z - 1, x + 1, z + 1, ny + 2, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny + 3, z, ID::PineLeave);
		builder.addLineZ(z - 1, z + 1, x, ny + 3, ID::PineLeave);

		builder.addLineY(ny + 4, ny + 5, x, z, ID::PineLeave);

		builder.addLineY(y, ny + 3, x, z, ID::PineWood);
	}

	HighLands::HighLands(int seed) :
		Biome(seed, 150, 100)
	{
		name = "HighLands";
	}

	ChunkBlock HighLands::getBeachBlock() {
		return ID::Stone;
	}

	ChunkBlock HighLands::getUnderwaterBlock() {
		return Rand::get().intInRange(0, 10) < 3 ? ID::Gravel : ID::Sand;
	}

	ChunkBlock HighLands::getUnderEarth()
	{
		if (!Rand::get().intInRange(0, 5))
			return ID::Iron;

		return ID::Stone;
	}

	ChunkBlock HighLands::getTopBlock() {
		return Rand::get().intInRange(0, 10) < 3 ? ID::Dirt : ID::Gravel;
	}

	ChunkBlock HighLands::getPlant() {

		return ID::Fern;
	}

	void HighLands::addTree(int x, int y, int z, Chunk* c) {

		StructureBuilder builder(c);

		int ny = y + Rand::get().intInRange(2, 3);

		builder.addLayer(x - 2, z - 1, x + 2, z + 1, ny, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny, z + 2, ID::PineLeave);
		builder.addLineX(x - 1, x + 1, ny, z - 2, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny + 1, z, ID::PineLeave);
		builder.addLineZ(z - 1, z + 1, x, ny + 1, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny + 2, z + 1, ID::PineLeave);
		builder.addLineX(x - 1, x + 1, ny + 2, z - 1, ID::PineLeave);

		builder.addLayer(x - 1, z - 1, x + 1, z + 1, ny + 2, ID::PineLeave);

		builder.addLineX(x - 1, x + 1, ny + 3, z, ID::PineLeave);
		builder.addLineZ(z - 1, z + 1, x, ny + 3, ID::PineLeave);

		builder.addLineY(ny + 4, ny + 5, x, z, ID::PineLeave);

		builder.addLineY(y, ny + 3, x, z, ID::PineWood);
	}

}