#pragma once

#include "glm/glm.hpp"

#include "AABB/AABB.h"

#include <array>

class Frustum {
public:
	void Update(const glm::mat4& mat) {
		//left
		planes[0].normal.x	= mat[0][3] + mat[0][0];
		planes[0].normal.y	= mat[1][3] + mat[1][0];
		planes[0].normal.z	= mat[2][3] + mat[2][0];
		planes[0].distance	= mat[3][3] + mat[3][0];

		// right
		planes[1].normal.x = mat[0][3] - mat[0][0];
		planes[1].normal.y = mat[1][3] - mat[1][0];
		planes[1].normal.z = mat[2][3] - mat[2][0];
		planes[1].distance = mat[3][3] - mat[3][0];

		// bottom
		planes[2].normal.x = mat[0][3] + mat[0][1];
		planes[2].normal.y = mat[1][3] + mat[1][1];
		planes[2].normal.z = mat[2][3] + mat[2][1];
		planes[2].distance = mat[3][3] + mat[3][1];

		// top
		planes[3].normal.x = mat[0][3] - mat[0][1];
		planes[3].normal.y = mat[1][3] - mat[1][1];
		planes[3].normal.z = mat[2][3] - mat[2][1];
		planes[3].distance = mat[3][3] - mat[3][1];

		// near
		planes[4].normal.x = mat[0][3] + mat[0][2];
		planes[4].normal.y = mat[1][3] + mat[1][2];
		planes[4].normal.z = mat[2][3] + mat[2][2];
		planes[4].distance = mat[3][3] + mat[3][2];

		// far
		planes[5].normal.x = mat[0][3] - mat[0][2];
		planes[5].normal.y = mat[1][3] - mat[1][2];
		planes[5].normal.z = mat[2][3] - mat[2][2];
		planes[5].distance = mat[3][3] - mat[3][2];


		for (plane& plane : planes) {
			float length = glm::length(plane.normal);
			plane.normal	/= length;
			plane.distance	/= length;
		}
	}

	bool isInFrustum(const AABB& o) {
		
		bool result = true;
		for (auto& plane : planes) {
			if (plane.distanceToPoint(o.getVP(plane.normal)) < 0)
				return false;
			else if (plane.distanceToPoint(o.getVN(plane.normal)) < 0)
				result = true;
		}
		return result;
	}

private:
	struct plane {
		glm::vec3 normal;
		float distance;

		float distanceToPoint(const glm::vec3& point) const {
			return glm::dot(point, normal) + distance;
		}
	};

	std::array<plane, 6> planes;
};
