#include "Context.h"

#include <GL/glew.h>
#include "Extern/Config.h"


Context::Context() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	if (Config::get().Fullscreen)
		window.create(sf::VideoMode::getDesktopMode(), "Minecraft", sf::Style::Fullscreen, settings);
	else 
		window.create(sf::VideoMode(Config::get().width, Config::get().height), "Minecraft", sf::Style::Close, settings);

	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	window.setActive(true);
}
