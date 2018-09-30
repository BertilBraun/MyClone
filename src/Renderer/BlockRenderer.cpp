#include "BlockRenderer.h"

#include "Texture/TextureAtlas.h"
#include "DataBase/DataBase.h"
#include "Loader/Loader.h"

namespace {
	std::vector<GLfloat> blockVertecies{
				0, 1, 1,
				1, 1, 1,
				1, 1, 0,
				0, 1, 0,

				0, 0, 1,
				1, 0, 1,
				1, 1, 1,
				0, 1, 1,

				1, 0, 0,
				0, 0, 0,
				0, 1, 0,
				1, 1, 0,

				1, 0, 1,
				1, 0, 0,
				1, 1, 0,
				1, 1, 1,

				0, 0, 0,
				0, 0, 1,
				0, 1, 1,
				0, 1, 0,

				0, 0, 0,
				1, 0, 0,
				1, 0, 1,
				0, 0, 1
	};

	std::vector<GLuint> blockIndicies{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};
}

BlockRenderer::BlockRenderer(const glm::mat4 & proj) {
	model.vao = Loader::get().GenVao();
	Loader::get().StoreData(0, 3, blockVertecies);
	vbo = Loader::get().StoreData(1, 2, std::vector<GLfloat>());
	Loader::get().StoreIndicies(blockIndicies);

	shader.Start();
	shader.loadProjectionMatrix(proj);
	shader.Stop();
}

void BlockRenderer::Render(Camera & camera) {

	if (!blocks.size())
		return;

	shader.Start();
	shader.loadViewMatrix();

	TextureAtlas::get().bind();

	for (block& b : blocks) {
		prepareInstance(b);
		GLCall(glBindVertexArray(model.vao));
		GLCall(glDrawElements(GL_TRIANGLES, model.size, GL_UNSIGNED_INT, nullptr));
	}

	shader.Stop();
	blocks.clear();
}

void BlockRenderer::processBlock(const glm::vec3 & pos, ID id, bool invSlot) {
	blocks.emplace_back(pos, id, invSlot);
}

void BlockRenderer::prepareInstance(block b) {
	auto insert = [&](std::vector<GLfloat>& toAdd, const std::vector<GLfloat>& data) {
		toAdd.insert(toAdd.end(), data.begin(), data.end());
	};

	glDeleteBuffers(1, &vbo);

	std::vector<GLfloat> data;

	insert(data, TextureAtlas::get().GetTextureCoords(DataBase::get().getBlock(b.id).textureUp));
	insert(data, TextureAtlas::get().GetTextureCoords(DataBase::get().getBlock(b.id).textureSide));
	insert(data, TextureAtlas::get().GetTextureCoords(DataBase::get().getBlock(b.id).textureSide));
	insert(data, TextureAtlas::get().GetTextureCoords(DataBase::get().getBlock(b.id).textureSide));
	insert(data, TextureAtlas::get().GetTextureCoords(DataBase::get().getBlock(b.id).textureSide));
	insert(data, TextureAtlas::get().GetTextureCoords(DataBase::get().getBlock(b.id).textureDown));

	vbo = Loader::get().StoreData(1, 2, data);

	glm::mat4 matrix;

	matrix = glm::rotate(matrix, glm::radians(45.0f), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(45.0f), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(0, 0, 1));

	matrix = glm::scale(glm::vec3(0.6f));

	matrix = glm::translate(matrix, b.pos);
	glm::mat4 mat;

	shader.loadModelMatrix(mat);
}
