#pragma once

#include "glm/gtx/transform.hpp"

#include "Entity/Camera.h"
#include "BaseShader.h"

class LeaveShader : public BaseShader {
public:
	LeaveShader() : BaseShader("Leave", "World") {
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
		GetUniform("timer");
		GetUniform("distance");
	}

public:
	void loadTime(float deltaTime) {
		SetUniform("timer", deltaTime);
	}

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