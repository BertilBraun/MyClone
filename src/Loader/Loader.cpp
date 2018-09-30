#include "Loader.h"

#include "Model/Model.h"
#include "Model/Mesh.h"
#include "World/Chunk/ChunkSection.h"

#include "defines.h"
#include "Extern/Config.h"

Loader::Loader() {

}

void Loader::UnBuffer(Model& model) {

	if (model.vao != 0) {
		GLCall(glDeleteVertexArrays(1, &model.vao));
		GLCall(glDeleteBuffers(model.vbos.size(), model.vbos.data()));
	}

	model.vbos.clear();

	model = Model();
}

void Loader::BufferMesh(ChunkSection& section) {

	auto buffer = [=](ChunkMesh& cm) {

		if (!cm.faces)
			return;

		Model* model = &cm.model; 
		Mesh* mesh = &cm.mesh;

		model->vao = GenVao();
		model->size = mesh->indicies.size();

		model->vbos.push_back(StoreData(0, 3, mesh->verticies));
		model->vbos.push_back(StoreData(1, 2, mesh->textures));
		model->vbos.push_back(StoreData(2, 3, mesh->normals));
		model->vbos.push_back(StoreData(3, 2, mesh->lights));
		model->vbos.push_back(StoreIndicies(mesh->indicies));

		mesh->verticies.clear();
		mesh->textures.clear();
		mesh->lights.clear();
		mesh->indicies.clear();

		mesh->verticies.shrink_to_fit();
		mesh->textures.shrink_to_fit();
		mesh->lights.shrink_to_fit();
		mesh->indicies.shrink_to_fit();
	};

	ChunkMeshCollection* coll = &section.getMeshes();

	if (section.isBuffered()) {
		coll->world.model.unBufferMesh();
		coll->water.model.unBufferMesh();
		coll->leave.model.unBufferMesh();
	}

	buffer(coll->world);
	buffer(coll->water);
	buffer(coll->leave);

	GLCall(glBindVertexArray(0));
}

GLuint Loader::LoadImage(sf::Image& image, const std::string& path) {

	if (!image.loadFromFile("res/Textures/" + path))
		return 0;

	return LoadImage(image);
}

GLuint Loader::LoadImage(const std::string& path) {

	sf::Image image;
	if (!image.loadFromFile("res/Textures/" + path))
		return 0;

	return LoadImage(image);
}

GLuint Loader::LoadImage(const sf::Image& image) {
	GLuint ID = 0;
	GLCall(glGenTextures(1, &ID));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	return ID;
}

GLuint Loader::StoreData(int attribNum, int dimensions, const std::vector<GLfloat>& data) {
	GLuint VboID;
	GLCall(glGenBuffers(1, &VboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(attribNum, dimensions, GL_FLOAT, GL_FALSE, 0, NULL));
	GLCall(glEnableVertexAttribArray(attribNum));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	return VboID;
}

GLuint Loader::StoreIndicies(const std::vector<GLuint>& data) {
	GLuint VboID;
	GLCall(glGenBuffers(1, &VboID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW));
	return VboID;
}

GLuint Loader::GenVao() {
	GLuint vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
	return vao;
}

GLuint Loader::LoadCubeMap(const std::string& path) {

	static const std::string pathadd[6] = { "right", "left", "top", "bottom", "back", "front" };

	GLuint ID = 0;
	GLCall(glGenTextures(1, &ID));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, ID));

	for (int i = 0; i < 6; i++) {
		sf::Image image;
		image.loadFromFile("res/Textures/" + path + pathadd[i] + ".png");
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

	return ID;
}