#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "Texture/Texture.h"
#include "Shader/BasicShader.h"

class Camera;

class BreakAnimRenderer {
public:
	BreakAnimRenderer(const glm::mat4& proj);
	~BreakAnimRenderer();

	void Render(Camera& camera);
	void processBlock(const glm::vec3& pos, float perComplete);

private:
	glm::vec3 pos;
	int index = 0;
	BasicShader shader;

	GLuint vao = 0;
	Texture textures[BREAK_ANIM_CNT];
};

