#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "DataBase/ID.h"
#include "Model/Model.h"

#include "Shader/BasicShader.h"

class Camera;

struct block {
	block(const glm::vec3& pos, ID id, bool invSlot) :
		pos(pos), id(id), invSlot(invSlot) { }

	glm::vec3 pos;
	ID id;
	bool invSlot = false;
};

class BlockRenderer {
public:
	BlockRenderer(const glm::mat4& proj);
	~BlockRenderer() {

	}

	void Render(Camera& camera);
	void processBlock(const glm::vec3& pos, ID id, bool invSlot = false);

private:
	void prepareInstance(block b);
	   	
	std::vector<block> blocks;
	Model model;
	GLuint vbo;

	BasicShader shader;
};