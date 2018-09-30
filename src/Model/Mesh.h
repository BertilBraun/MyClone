#pragma once

#include "GL/glew.h"
#include <vector>

struct Mesh {
	std::vector<GLfloat> verticies;
	std::vector<GLfloat> textures;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> lights;

	std::vector<GLuint> indicies;
};
