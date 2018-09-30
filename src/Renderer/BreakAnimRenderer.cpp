#include "BreakAnimRenderer.h"

#include "defines.h"
#include "Loader/Loader.h"
#include "Entity/Camera.h"

namespace {

	std::vector<GLfloat> vertecies{
			0, 1, 1,
			1, 1, 1,
			1, 1, 0,
			1, 1, 0,
			0, 1, 0,
			0, 1, 1,

			0, 0, 1,
			1, 0, 1,
			1, 1, 1,
			1, 1, 1,
			0, 1, 1,
			0, 0, 1,

			1, 0, 0,
			0, 0, 0,
			0, 1, 0,
			0, 1, 0,
			1, 1, 0,
			1, 0, 0,

			1, 0, 1,
			1, 0, 0,
			1, 1, 0,
			1, 1, 0,
			1, 1, 1,
			1, 0, 1,

			0, 0, 0,
			0, 0, 1,
			0, 1, 1,
			0, 1, 1,
			0, 1, 0,
			0, 0, 0,

			0, 0, 0,
			1, 0, 0,
			1, 0, 1,
			1, 0, 1,
			0, 0, 1,
			0, 0, 0
	};

	std::vector<GLfloat> texturecoords{
		0, 0,
		1, 0,
		1, 1,
		1, 1,
		0, 1,
		0, 0,

		0, 0,
		1, 0,
		1, 1,
		1, 1,
		0, 1,
		0, 0,

		0, 0,
		1, 0,
		1, 1,
		1, 1,
		0, 1,
		0, 0,

		0, 0,
		1, 0,
		1, 1,
		1, 1,
		0, 1,
		0, 0,

		0, 0,
		1, 0,
		1, 1,
		1, 1,
		0, 1,
		0, 0,

		0, 0,
		1, 0,
		1, 1,
		1, 1,
		0, 1,
		0, 0
	};

}

BreakAnimRenderer::BreakAnimRenderer(const glm::mat4& proj) {
	vao = Loader::get().GenVao();

	Loader::get().StoreData(0, 3, vertecies);
	Loader::get().StoreData(1, 2, texturecoords);
	GLCall(glBindVertexArray(0));

	for (int i = 0; i < BREAK_ANIM_CNT; i++)
		textures[i].ID = Loader::get().LoadImage("Animations/mining/mining" + std::to_string(i) + ".png");

	shader.Start();
	shader.loadProjectionMatrix(proj);
	shader.Stop();
}


BreakAnimRenderer::~BreakAnimRenderer()
{
}


void BreakAnimRenderer::Render(Camera & camera) {

	shader.Start();
	shader.loadViewMatrix(camera);

	GLCall(glBindVertexArray(vao));

	textures[index].bind();

	shader.loadModelMatrix(glm::translate(pos));

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	GLCall(glBindVertexArray(0));

	shader.Stop();
}

void BreakAnimRenderer::processBlock(const glm::vec3 & pos, float perComplete) {
	this->pos = pos;
	index = (int)(perComplete * 10.0f);
}
