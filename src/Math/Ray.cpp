#include "Ray.h"

#include "World/World.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& dir) :
	origin(origin)
,	dir(dir)
,	end(origin)
{
}

void Ray::Step(float step) {
	end += dir * step;

	length = glm::length(end - origin);
}

GLfloat Ray::getLength() {
	return length;
}

glm::vec3 Ray::getEnd() {
	return end;
}

RayCast::RayCast(World * world) :
	world(world)
{ }

glm::ivec3 RayCast::cast(const glm::vec3 & origin, const glm::vec3 & dir) {
	
	for (Ray ray(origin, dir); ray.getLength() < DIG_DISTANCE; ray.Step(STEP_SIZE)) {

		glm::ivec3 r = glm::ivec3(ray.getEnd());

		if (world->getBlock(r.x, r.y, r.z).id != ID::Air)
			return r;
	}
	
	return { 0,0,0 };
}
