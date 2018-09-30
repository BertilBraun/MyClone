#pragma once

#include "glm/glm.hpp"
#include "SFML/Window/Window.hpp"
#include "Math/Frustum.h"

#include "Entity.h"

class Application;

class Camera {
public:
	Camera(Application* app);

	void Update(const sf::Window& w, bool resetPos);
	void HookEntity(Entity* e);
	void unHook();

	glm::vec3 const getPos() const;

	glm::vec3 forward { 0, 0, -1 };
	glm::vec3 right { 0, 0, 0 };
	glm::vec3 up { 0, 0, 0 };

	const glm::mat4& getViewMat() const;
	const glm::mat4& getProjMat() const;

	bool isBoxInFrustum(const AABB& o);
private:
	Entity * entity = nullptr;
	Frustum frustum;

	glm::vec2 rot{ 1.57079632679f, 0.0f };
	glm::mat4 view, proj;

};

