#pragma once

#include "glm/glm.hpp"

class AABB {
public:
	AABB(const glm::vec3& dim = glm::vec3(1));

	void SetDim(const glm::vec3& dim);
	void UpdatePos(const glm::vec3& pos);

	bool Collided(const AABB& o);
	bool Collided(const glm::vec3& o);
	
	glm::vec3 getVN(const glm::vec3& normal) const;
	glm::vec3 getVP(const glm::vec3& normal) const;

	glm::vec3 dim, min, max;
};