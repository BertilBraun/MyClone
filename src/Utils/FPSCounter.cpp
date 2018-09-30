#include "FPSCounter.h"

#include <iostream>
#include "DataBase/DataBase.h"

FPSCounter::FPSCounter()
{ 
	text = DataBase::get().getText();
	text.move(10, 10);
}


void FPSCounter::update() {
	frameCount++;

	if (delayTimer.getElapsedTime().asSeconds() > 0.5) {
		fps = frameCount / fpsTimer.restart().asSeconds();
		frameCount = 0;
		delayTimer.restart();
		text.setString("FPS: " + std::to_string(fps));
	}
}


