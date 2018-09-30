#pragma once

#include "AABB.h"

AABB::AABB(const glm::vec3& dim) : dim(dim) {

}

void AABB::SetDim(const glm::vec3 & dim) {
	this->dim = dim;
}

void AABB::UpdatePos(const glm::vec3& pos) {
	min = pos;
	max = pos + dim;
}

bool AABB::Collided(const AABB& o) {
	return	(min.x <= o.max.x && max.x >= o.min.x) &&
			(min.y <= o.max.y && max.y >= o.min.y) &&
			(min.z <= o.max.z && max.z >= o.min.z);
}

bool AABB::Collided(const glm::vec3& o) {
	return	(o.x >= min.x && o.x <= max.x) &&
			(o.y >= min.y && o.y <= max.y) &&
			(o.z >= min.z && o.z <= max.z);
}

glm::vec3 AABB::getVN(const glm::vec3 & normal) const {
	
	glm::vec3 res = min;

	if (normal.x < 0)
		res.x += dim.x;
	if (normal.y < 0)
		res.y += dim.y;
	if (normal.z < 0)
		res.z += dim.z;

	return res;
}

glm::vec3 AABB::getVP(const glm::vec3 & normal) const {

	glm::vec3 res = min;

	if (normal.x > 0)
		res.x += dim.x;
	if (normal.y > 0)
		res.y += dim.y;
	if (normal.z > 0)
		res.z += dim.z;

	return res;
}
