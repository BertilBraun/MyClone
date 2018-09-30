#pragma once

#include "Loader/Loader.h"
#include "Texture.h"
#include <string>
#include "defines.h"

class CubeTexture : public Texture {
public:
	CubeTexture(const std::string& path) {
		ID = Loader::get().LoadCubeMap(path);
	}

	void bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	}
};