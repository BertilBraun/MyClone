#include "Craft2x2.h"

Craft2x2::Craft2x2(Application * app, Inventory * inv) :
	result(glm::vec2(0.73, 0.315), glm::vec2(0.045, 0.06), (*app->getWindow())),
	inv(inv),
	shift(sf::Keyboard::Key::LShift)
{
	comp.reserve(SLOTS);

	for (int i = 0; i < SLOTS; i++)
		comp.emplace_back(glm::vec2(0.555 + (i % 2) * 0.0563, 0.34 - (float)((int)(i / 2)) * 0.068),
			glm::vec2(0.045, 0.06), (*app->getWindow()));

}

void Craft2x2::render(MasterRenderer & renderer) {

	for (int i = 0; i < SLOTS; i++)
		comp[i].draw(renderer);

	result.draw(renderer);
}

void Craft2x2::update(Component & selectedComp) {

	for (int i = 0; i < SLOTS; i++) {
		if (comp[i].pressed()) {

			if (comp[i].slot != Slot()) {

				int v = selectedComp.slot.getStackSize();
				selectedComp.slot = comp[i].slot;
				comp[i].slot.setStackSize(selectedComp.slot.add(v));

				if (!comp[i].slot.getStackSize())
					comp[i].slot = Slot();
			}
			else if (selectedComp.slot != Slot()) {

				comp[i].setSlot(selectedComp.slot);
				selectedComp.resetSlot();
			}
			comp[i].update();
			selectedComp.update();
			result.resetSlot();
			tryRecepies();
			break;
		}
		if (comp[i].pressedR()) {

			if (comp[i].slot != Slot()) {
				if (selectedComp.slot != Slot())
					break;

				int v = 1 + selectedComp.slot.getStackSize();
				selectedComp.slot = comp[i].slot;
				selectedComp.slot.setStackSize(v);

				comp[i].removeOne();
			}
			else if (selectedComp.slot != Slot()) {

				Slot slot = selectedComp.slot;
				selectedComp.removeOne();

				if (comp[i].slot == Slot()) {
					comp[i].slot = slot;
					comp[i].slot.setStackSize(1);
				}
				else
					comp[i].slot.add(1);
			}
			comp[i].update();
			selectedComp.update();
			result.resetSlot();
			tryRecepies();
			break;
		}
	}

	if (result.pressed()) {
		if (result.slot != Slot()) {

			if (shift.isKeyPressed()) {

				inv->add(result.slot);

				for (int i = 0; i < SLOTS; i++)
					comp[i].removeOne();

			}
			else {

				if (selectedComp.slot == Slot()) {

					for (int i = 0; i < SLOTS; i++)
						comp[i].removeOne();

					selectedComp.setSlot(result.slot);
				}
			}
			result.resetSlot();
			tryRecepies();
		}
	}
}

void Craft2x2::tryRecepies() {

	for (auto& rec : recep.recepies) {
		if (rec.doesFit(comp)) {
			result.setSlot(rec.getResult());
			break;
		}
	}
}
