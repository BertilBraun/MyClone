#pragma once

#include "glm/gtx/transform.hpp"

#include "Entity/Camera.h"
#include "BaseShader.h"

class BasicShader : public BaseShader {
public:
	BasicShader() : BaseShader("Basic", "Basic") {
		BindAttribs();
		GetUniformLocations();
	}

private:
	void BindAttribs() {
		BindAttribute(0, "VertPosition");
		BindAttribute(1, "VertTexture");
	}

	void GetUniformLocations() {
		GetUniform("ProjMatrix");
		GetUniform("ViewMatrix");
		GetUniform("ModelMatrix");
	}

public:
	void loadProjectionMatrix(const glm::mat4& projection) {
		SetUniform("ProjMatrix", projection);
	}

	void loadViewMatrix(const Camera& camera) {
		SetUniform("ViewMatrix", camera.getViewMat());
	}

	void loadViewMatrix() {
		SetUniform("ViewMatrix", glm::mat4(1));
	}

	void loadModelMatrix(const glm::mat4& model) {
		SetUniform("ModelMatrix", model);
	}
};