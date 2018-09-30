#pragma once

#include "GL/glew.h"

class Texture {
public:
	Texture();
	~Texture();

	void bind();

	GLuint ID = 0;
};
