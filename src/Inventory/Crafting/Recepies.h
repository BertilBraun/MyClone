#pragma once

#include "BaseRecepie.h"

struct Recepies {

	std::vector<BaseRecepie> recepies {

		//PLANK
		BaseRecepie(glm::ivec2(1), Slot(ID::Plank, 4)).
			addMaterial(glm::ivec2(0), Slot(ID::Wood, 1)),

		//WOOD
		BaseRecepie(glm::ivec2(2), Slot(ID::Wood, 1)).
			addMaterial(glm::ivec2(0, 0), Slot(ID::Plank, 1)).
			addMaterial(glm::ivec2(0, 1), Slot(ID::Plank, 1)).
			addMaterial(glm::ivec2(1, 0), Slot(ID::Plank, 1)).
			addMaterial(glm::ivec2(1, 1), Slot(ID::Plank, 1)),

		//AXE
		BaseRecepie(glm::ivec2(3), Slot(ItID::AXE)).
			addMaterial(glm::ivec2(1, 0), Slot(ID::Plank, 1)).
			addMaterial(glm::ivec2(1, 1), Slot(ID::Plank, 1)).
			addMaterial(glm::ivec2(0, 2), Slot(ID::Wood, 1)).
			addMaterial(glm::ivec2(1, 2), Slot(ID::Wood, 1)).
			addMaterial(glm::ivec2(2, 2), Slot(ID::Wood, 1)),

		//GLASS
		BaseRecepie(glm::ivec2(2), Slot(ID::Glass, 4)).
			addMaterial(glm::ivec2(0, 0), Slot(ID::Sand, 1)).
			addMaterial(glm::ivec2(0, 1), Slot(ID::Sand, 1)).
			addMaterial(glm::ivec2(1, 0), Slot(ID::Sand, 1)).
			addMaterial(glm::ivec2(1, 1), Slot(ID::Sand, 1)),
	};

	/*const static BaseRecepie Sword = BaseRecepie(glm::ivec2(3), Slot(ItID::AXE)).
		addMaterial(glm::ivec2(0), Slot(ID::Plank, 1)).
		addMaterial(glm::ivec2(0, 1), Slot(ID::Plank, 1)).
		addMaterial(glm::ivec2(1, 0), Slot(ID::Plank, 1)).
		addMaterial(glm::ivec2(1), Slot(MID::IRON, 1)).
		addMaterial(glm::ivec2(2), Slot(MID::IRON, 1));*/
};