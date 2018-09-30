#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include <string>

#include "Texture/CubeTexture.h"
#include "Shader/SkyboxShader.h"

class Camera;

class SkyboxRenderer {
public:
	SkyboxRenderer(const glm::mat4& proj, const std::string& path = "");

	void Render(Camera& camera);
private:
	CubeTexture texture;
	SkyboxShader shader;
	GLuint vao;
};