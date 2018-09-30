#include "WorldRenderer.h"

#include "Entity/Camera.h"
#include "Texture/TextureAtlas.h"

#include "World/Chunk/ChunkSection.h"

WorldRenderer::WorldRenderer(const glm::mat4& proj) {

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
 
void WorldRenderer::Render(Camera& camera, float deltaTime) {

	static float Timer = 0;
	Timer += deltaTime;

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

	if (water.size()) {

		waterShader.Start();
		waterShader.loadViewMatrix(camera);
		waterShader.loadLightPos({ 0.45, 0.82, -0.35 });
		waterShader.loadTime(Timer);

		GLCall(glDisable(GL_CULL_FACE));
		TextureAtlas::get().bind();

		for (Model& model : water) {
			GLCall(glBindVertexArray(model.vao));
			GLCall(glDrawElements(GL_TRIANGLES, model.size, GL_UNSIGNED_INT, nullptr));
		}

		waterShader.Stop();
		water.clear();
	}

	if (leave.size()) {

		leaveShader.Start();
		leaveShader.loadViewMatrix(camera);
		leaveShader.loadLightPos({ 0.45, 0.82, -0.35 });
		leaveShader.loadTime(Timer);

		TextureAtlas::get().bind();

		for (Model& model : leave) {
			GLCall(glBindVertexArray(model.vao));
			GLCall(glDrawElements(GL_TRIANGLES, model.size, GL_UNSIGNED_INT, nullptr));
		}

		leaveShader.Stop();
		leave.clear();
	}

	GLCall(glBindVertexArray(0));
}

void WorldRenderer::ProcessChunkSection(ChunkSection& cs) {
	ChunkMeshCollection& collection = cs.getMeshes();

	if (collection.world.faces)
		world.emplace_back(collection.world.model);

	if (collection.water.faces)
		water.emplace_back(collection.water.model);

	if (collection.leave.faces)
		leave.emplace_back(collection.leave.model);
}
