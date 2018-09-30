#pragma once

#include <vector>

#include "Shader/WorldShader.h"
#include "Shader/WaterShader.h"
#include "Shader/LeaveShader.h"

#include "Model/Model.h"

class ChunkSection;
class Camera;

class WorldRenderer {
public:
	WorldRenderer(const glm::mat4& proj);

	void Render(Camera& camera, float deltaTime);

	void ProcessChunkSection(ChunkSection& cs);

private:
	WorldShader worldShader;
	WaterShader waterShader;
	LeaveShader leaveShader;

	std::vector<Model> world, water, leave;
};