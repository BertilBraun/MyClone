#include "Texture.h"
#include "defines.h"

Texture::Texture() {

}


Texture::~Texture() {
	glDeleteTextures(1, &ID);
}

void Texture::bind() {
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));
}