#include "BaseRecepie.h"

BaseRecepie::BaseRecepie(const glm::ivec2 & size, const Slot & result) :
	size(size),
	result(result)
{
	slots.resize(size.x * size.y);
}

BaseRecepie & BaseRecepie::addMaterial(const glm::ivec2 & pos, const Slot & slot) {

	if (pos.x >= size.x || pos.x < 0 || pos.y >= size.y || pos.y < 0)
		return *this;

	slots[pos.x + pos.y * size.x] = slot;
	return *this;
}

bool BaseRecepie::doesFit(std::vector<Component>& inv) {
	glm::ivec2 invSize(sqrt(inv.size()));

	if (size.x > invSize.x || size.y > invSize.y)
		return false;

	bool correct = true;

	for (int ox = 0; size.x + ox <= invSize.x; ox++)
		for (int oy = 0; size.y + oy <= invSize.y; oy++) {
			correct = true;

	//int ox = 0, oy = 0;

			for (int x = 0; x < invSize.x; x++) {
				for (int y = 0; y < invSize.y; y++) {
					if (x >= ox && x < ox + size.x && y >= oy && y < oy + size.y) {
						if (inv[x + invSize.x * y].slot != slots[x - ox + size.x * (y - oy)]) {
							correct = false;
							break;
						}
					}
					else {
						if (inv[x + invSize.x * y].slot != Slot()) {
							correct = false;
							break;
						}
					}
				}

				if (!correct)
					break;
			}
			if (correct)
				return true;
		}
	
	return correct;
}

Slot & BaseRecepie::getResult() {
	return result;
}
