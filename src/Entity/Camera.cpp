#include "Camera.h"

#include "SFML/Graphics.hpp"
#include "Extern/Config.h"

#include "glm/gtx/transform.hpp"
#include "Application.h"

#include "defines.h"

Camera::Camera(Application* app) :
	proj(glm::perspective((float)(Config::get().FOV), (float)((*app->getWindow()).getSize().x) / (float)((*app->getWindow()).getSize().y), Z_NEAR, Z_FAR))
{
	
}

void Camera::Update(const sf::Window& w, bool resetPos) {
	
	sf::Vector2i pos = sf::Mouse::getPosition(w);

	if (resetPos) {
		sf::Mouse::setPosition(sf::Vector2i(400, 400), w);

		rot.x += (float)Config::get().mouseSpeed * (400 - pos.x);
		rot.y += (float)Config::get().mouseSpeed * (400 - pos.y);
	}

	//1.57079632679 == PI / 2
	if (rot.y > 1.5707)
		rot.y = 1.5707f;

	if (rot.y < -1.5707)
		rot.y = -1.5707f;

	forward = glm::normalize(glm::vec3(cosf(rot.y) * sinf(rot.x), sinf(rot.y), cosf(rot.y) * cosf(rot.x)));
	
	right	= glm::normalize(glm::cross(forward, { 0, 1, 0 }));
	up		= glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(this->getPos(), this->getPos() + forward, up);
	frustum.Update(proj * view);
}

void Camera::HookEntity(Entity* e) {
	entity = e;
}

void Camera::unHook() {
	entity = nullptr;
}

glm::vec3 const Camera::getPos() const {
	if (entity != nullptr)
		return entity->getPos();
	return { 0,0,0 };
}

const glm::mat4& const Camera::getViewMat() const {
	return view;
}

const glm::mat4& const Camera::getProjMat() const {
	return proj;
}

bool Camera::isBoxInFrustum(const AABB& o) {
	return frustum.isInFrustum(o);
}