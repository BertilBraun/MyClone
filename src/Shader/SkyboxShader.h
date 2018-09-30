#pragma once

#include "glm/gtx/transform.hpp"
#include "BaseShader.h"
#include "Entity/Camera.h"

class SkyboxShader : public BaseShader {
public:
	SkyboxShader() : BaseShader("Skybox", "Skybox") {
		BindAttribs();
		GetUniformLocations();
	}

private:
	void BindAttribs() {
		BindAttribute(0, "VertPosition");
	}

	void GetUniformLocations() {
		GetUniform("ProjMatrix");
		GetUniform("ViewMatrix");
	}

public:
	void loadProjectionMatrix(glm::mat4 projection) {
		SetUniform("ProjMatrix", projection);
	}

	void loadViewMatrix(const Camera& camera) {
		glm::mat4 view = camera.getViewMat();
		view[3][0] = 0;
		view[3][1] = 0;
		view[3][2] = 0;
		SetUniform("ViewMatrix", view);
	}
};