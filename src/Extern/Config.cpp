#include "Config.h"
#include <fstream>
#include <string>
#include <iostream>

Config::Config() {
	load("res/config.txt");
}

void Config::load(const char * path) {
	std::ifstream s(path);
	std::string line;

	if (!s.good()) {
		std::cout << "Couldnt load Config" << std::endl;
		return;
	}

	while (std::getline(s, line)) {
		if (line == "Fullscreen") {
			s >> Fullscreen;
		}
		else if (line == "width") {
			s >> width;
		}
		else if (line == "height") {
			s >> height;
		}
		else if (line == "FOV") {
			s >> FOV;
		}
		else if (line == "indivTextureWidth") {
			s >> indivTextureWidth;
		}
		else if (line == "mouseSpeed") {
			s >> mouseSpeed;
			mouseSpeed *= 0.001;
		}
		else if (line == "renderDistance") {
			s >> renderDistance;
		}
	}
}

