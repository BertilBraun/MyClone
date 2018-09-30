#pragma once

#include "Event.h"

class WorldEvent {
public:
	WorldEvent(const EventType& et) : et(et) {
	}

	virtual bool Update(float deltaTime) = 0;
	virtual void Display(MasterRenderer& renderer) {}

	EventType getEventType() { return et; }

protected:
	EventType et;
};
