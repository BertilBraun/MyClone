#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

class World;

class Ray {
public:
	Ray(const glm::vec3& origin, const glm::vec3& dir);

	void Step(float step);
	GLfloat getLength();
	glm::vec3 getEnd();

private:
	GLfloat length = 0;
	glm::vec3 origin, dir, end;
};

class RayCast {
public:
	RayCast(World* world);

	glm::ivec3 cast(const glm::vec3& origin, const glm::vec3& dir);

private:
	World* world;
};