#pragma once

#include "Utils/CopyInhertance.h"

class Config : public Singleton {
public:

	static Config& get() { static Config c; return c; }

	//Config
	bool Fullscreen = false;
	int width = 800;
	int height = 600;
	int indivTextureWidth = 16;


	//Settings
	int FOV = 90;
	float mouseSpeed = 0.001f;
	float movementSpeed = 2.0f;
	int renderDistance = 8;

private:
	void load(const char * path);
	Config();
};

