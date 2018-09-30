#pragma once

#include "GL/glew.h"
#include <vector>

class Model {
public:
	Model();
	void unBufferMesh();
	
	GLuint vao = 0;
	std::vector<GLuint> vbos;
	GLuint size = 0;
};