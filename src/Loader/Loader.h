#pragma once

#include <glm/glm.hpp>
#include "SFML/Graphics/Image.hpp"
#include "GL/glew.h"
#include <vector>
#include <string>

#include "Utils/CopyInhertance.h"

class Model;
struct Mesh;
class ChunkSection;

class Loader : public Singleton {
public:
	static Loader& get() { static Loader loader; return loader; }

	void BufferMesh(ChunkSection& mesh);
	void UnBuffer(Model& mesh);

	GLuint LoadImage(sf::Image& image, const std::string& path);
	GLuint LoadImage(const std::string& path);
	GLuint LoadImage(const sf::Image& image);
	GLuint LoadCubeMap(const std::string& path);

	GLuint StoreData(int attribNum, int dimensions, const std::vector<GLfloat>& data);
	GLuint StoreIndicies(const std::vector<GLuint>& data);
	GLuint GenVao();

private:
	Loader();
};


