#include "Application.h"
#include <iostream>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#ifdef __WIN32
	extern "C" {
		//Enable dedicated graphics
		__declspec(dllexport) bool NvOptimusEnablement = true;
		__declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
	}
#endif // __WIN32
	
int main() {
	Application app;
	app.runLoop();
}
