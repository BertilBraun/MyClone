#pragma once

#include "glm/gtx/transform.hpp"

#include "Entity/Camera.h"
#include "BaseShader.h"

class WorldShader : public BaseShader {
public:
	WorldShader() : BaseShader("World", "World") {
		BindAttribs();
		GetUniformLocations();
	}

private:
	void BindAttribs() {
		BindAttribute(0, "VertPosition");
		BindAttribute(1, "VertTexture");
		BindAttribute(2, "VertNormal");
		BindAttribute(3, "VertLight");
	}

	void GetUniformLocations() {
		GetUniform("ProjMatrix");
		GetUniform("ViewMatrix");
		GetUniform("lightPos");
		GetUniform("distance");
	}

public:
	void loadProjectionMatrix(glm::mat4 projection) {
		SetUniform("ProjMatrix", projection);
	}

	void loadViewMatrix(const Camera& camera) {
		SetUniform("ViewMatrix", camera.getViewMat());
	}

	void loadLightPos(const glm::vec3& pos) {
		SetUniform("lightPos", pos);
	}

	void loadRenderDistance(float pos) {
		SetUniform("distance", pos);
	}
};