#pragma once

#include "glm/glm.hpp"
#include <vector>

#include "Inventory/Component.h"

class BaseRecepie {
public:
	BaseRecepie(const glm::ivec2& size, const Slot& result);

	BaseRecepie& addMaterial(const glm::ivec2& pos, const Slot& slot);

	bool doesFit(std::vector<Component>& inv);

	Slot& getResult();

private:
	glm::ivec2 size;
	std::vector<Slot> slots;
	Slot result;
};
