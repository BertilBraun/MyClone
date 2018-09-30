#include "SFMLRenderer.h"

#include <GL/glew.h>

void SFMLRenderer::add(const sf::Drawable& drawable) {
	draws.push_back(&drawable);
}

void SFMLRenderer::render(sf::RenderWindow& window) {
	if (draws.empty())
		return;

	glDisable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);

	window.pushGLStates();
	window.resetGLStates();

	for (const auto& draw : draws) 
		window.draw(*draw);
	

	window.popGLStates();
	draws.clear();
}
