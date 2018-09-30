#include "TextureAtlas.h"

#include "Loader/Loader.h"
#include "Extern/Config.h"

#include "SFML/Graphics/Image.hpp"

std::vector<GLfloat> TextureAtlas::GetTextureCoords(const glm::ivec2& off) {

	static float indivTextureW = 1 / (GLfloat)floor(texSize / Config::get().indivTextureWidth);

	GLfloat	x0 = off.x * indivTextureW,
			y0 = off.y * indivTextureW,
			x1 = x0 + indivTextureW,
			y1 = y0 + indivTextureW;

	return {
		x1, y1,
		x0, y1,
		x0, y0,
		x1, y0
	};
}

TextureAtlas::TextureAtlas(const std::string& path) {
	sf::Image i;
	if (!i.loadFromFile("res/Textures/ResourcePacks/" + path + ".png"))
		throw std::runtime_error("Texture Atlas" + path + " didnt load sucessfully\n");
	texSize = i.getSize().x;
	ID = Loader::get().LoadImage(i);
}