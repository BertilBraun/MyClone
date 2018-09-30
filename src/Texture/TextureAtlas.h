#pragma once

#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"

#include "Texture.h"
#include "Utils/CopyInhertance.h"

class TextureAtlas : public Texture , public Singleton {
public:
	static TextureAtlas& get() { static TextureAtlas t("DefaultPack"); return t; }

	std::vector<GLfloat> GetTextureCoords(const glm::ivec2& off);

private:
	TextureAtlas(const std::string& path);

	GLuint texSize = 1;
};