#include "MasterRenderer.h"

#include "Application.h"

#include "Extern/Config.h"
#include "Extern/Context.h"

#include "glm/gtx/transform.hpp"
#include "defines.h"

#include "Texture/TextureAtlas.h"
#include "World/Chunk/ChunkSection.h"

std::vector<GLfloat> vertex {
	-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

	-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
	-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,

	-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
	-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

	-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
	-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

	-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE
};

std::vector<GLfloat> vertecies{
			-0.01, 1.01, 1.01,
			1.01, 1.01, 1.01,
			1.01, 1.01, -0.01,
			1.01, 1.01, -0.01,
			-0.01, 1.01, -0.01,
			-0.01, 1.01, 1.01,

			-0.01, -0.01, 1.01,
			1.01, -0.01, 1.01,
			1.01, 1.01, 1.01,
			1.01, 1.01, 1.01,
			-0.01, 1.01, 1.01,
			-0.01, -0.01, 1.01,

			1.01, -0.01, -0.01,
			-0.01, -0.01, -0.01,
			-0.01, 1.01, -0.01,
			-0.01, 1.01, -0.01,
			1.01, 1.01, -0.01,
			1.01, -0.01, -0.01,

			1.01, -0.01, 1.01,
			1.01, -0.01, -0.01,
			1.01, 1.01, -0.01,
			1.01, 1.01, -0.01,
			1.01, 1.01, 1.01,
			1.01, -0.01, 1.01,

			-0.01, -0.01, -0.01,
			-0.01, -0.01, 1.01,
			-0.01, 1.01, 1.01,
			-0.01, 1.01, 1.01,
			-0.01, 1.01, -0.01,
			-0.01, -0.01, -0.01,

			-0.01, -0.01, -0.01,
			1.01, -0.01, -0.01,
			1.01, -0.01, 1.01,
			1.01, -0.01, 1.01,
			-0.01, -0.01, 1.01,
			-0.01, -0.01, -0.01
};

std::vector<GLfloat> textures {
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

MasterRenderer::MasterRenderer(const glm::mat4& proj) :
	projectionMatrix(proj)
,	breakAnimRenderer(projectionMatrix)
,	skyboxRenderer(projectionMatrix)
,	worldRenderer(projectionMatrix)
,	blockRenderer(projectionMatrix)
,	texture("Skybox/")
{
	svao = Loader::get().GenVao();
	Loader::get().StoreData(0, 3, vertex);
	GLCall(glBindVertexArray(0));

	sshader.Start();
	sshader.loadProjectionMatrix(proj);
	sshader.Stop();

	bvao = Loader::get().GenVao();

	Loader::get().StoreData(0, 3, vertecies);
	Loader::get().StoreData(1, 2, textures);
	GLCall(glBindVertexArray(0));

	for (int i = 0; i < BREAK_ANIM_CNT; i++)
		btextures[i].ID = Loader::get().LoadImage("Animations/mining/mining" + std::to_string(i) + ".png");

	bshader.Start();
	bshader.loadProjectionMatrix(proj);
	bshader.Stop();

	worldShader.Start();
	worldShader.loadProjectionMatrix(proj);
	worldShader.loadRenderDistance((1 / ((float)Config::get().renderDistance * 10)));
	worldShader.Stop();
	waterShader.Start();
	waterShader.loadProjectionMatrix(proj);
	waterShader.loadRenderDistance((1 / ((float)Config::get().renderDistance * 10)));
	waterShader.Stop();
	leaveShader.Start();
	leaveShader.loadProjectionMatrix(proj);
	leaveShader.loadRenderDistance((1 / ((float)Config::get().renderDistance * 10)));
	leaveShader.Stop();
}


MasterRenderer::~MasterRenderer() {
}

void MasterRenderer::ProcessSFML(const sf::Drawable& draw) {
	sfmlRenderer.add(draw);
}

void MasterRenderer::ProcessChunkSection(ChunkSection& cs) {

	//worldRenderer.ProcessChunkSection(cs);

	ChunkMeshCollection& collection = cs.getMeshes();

	if (collection.world.faces)
		world.emplace_back(collection.world.model);

	if (collection.water.faces)
		water.emplace_back(collection.water.model);

	if (collection.leave.faces)
		leave.emplace_back(collection.leave.model);
}

void MasterRenderer::ProcessBreakAnim(const glm::vec3 & pos, float p){
	//breakAnimRenderer.processBlock(pos, p);

	bshouldRender = true;
	bpos = pos;
	bindex = (int)(p * 10.0f);
}

void MasterRenderer::ProcessBlock(const glm::vec3 & pos, ID id, bool invSlot) {

	//blockRenderer.processBlock(pos, id, invSlot);
}

void MasterRenderer::Render(sf::RenderWindow& window, Camera& camera, float deltaTime) {

	static float Timer = 0;
	Timer += deltaTime;

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glClearColor(0.52f, 0.80f, 0.92f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	//if (renderSkybox)
		//skyboxRenderer.Render(camera);
	//worldRenderer.Render(camera, deltaTime);
	//breakAnimRenderer.Render(camera);
	//blockRenderer.Render(camera);

	if (renderSkybox) {
		sshader.Start();
		sshader.loadViewMatrix(camera);

		texture.bind();

		GLCall(glBindVertexArray(svao));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

		GLCall(glBindVertexArray(0));

		sshader.Stop();
		renderSkybox = false;
	}
	
	if (world.size()) {

		worldShader.Start();
		worldShader.loadViewMatrix(camera);
		worldShader.loadLightPos({ 0.45, 0.82, -0.35 });

		TextureAtlas::get().bind();

		for (Model& model : world) {
			GLCall(glBindVertexArray(model.vao));
			GLCall(glDrawElements(GL_TRIANGLES, model.size, GL_UNSIGNED_INT, nullptr));
		}

		worldShader.Stop();
		world.clear();
	}

	if (leave.size()) {

		leaveShader.Start();
		leaveShader.loadViewMatrix(camera);
		leaveShader.loadLightPos({ 0.45, 0.82, -0.35 });
		leaveShader.loadTime(Timer);

		GLCall(glDisable(GL_CULL_FACE));
		TextureAtlas::get().bind();

		for (Model& model : leave) {
			GLCall(glBindVertexArray(model.vao));
			GLCall(glDrawElements(GL_TRIANGLES, model.size, GL_UNSIGNED_INT, nullptr));
		}

		leaveShader.Stop();
		leave.clear();
	}

	if (water.size()) {

		waterShader.Start();
		waterShader.loadViewMatrix(camera);
		waterShader.loadLightPos({ 0.45, 0.82, -0.35 });
		waterShader.loadTime(Timer);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		TextureAtlas::get().bind();

		for (Model& model : water) {
			GLCall(glBindVertexArray(model.vao));
			GLCall(glDrawElements(GL_TRIANGLES, model.size, GL_UNSIGNED_INT, nullptr));
		}

		waterShader.Stop();
		water.clear();
	}

	GLCall(glBindVertexArray(0));

	if (bshouldRender) {
		bshader.Start();
		bshader.loadViewMatrix(camera);

		GLCall(glBindVertexArray(bvao));

		btextures[bindex].bind();

		bshader.loadModelMatrix(glm::translate(bpos));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		GLCall(glBindVertexArray(0));

		bshader.Stop();
	}
	bshouldRender = false;

	sfmlRenderer.render(window);
}

void MasterRenderer::RenderSkybox() {
	renderSkybox = true;
}
