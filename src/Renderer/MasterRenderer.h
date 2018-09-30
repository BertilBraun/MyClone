#pragma once

#include "BreakAnimRenderer.h"
#include "SkyboxRenderer.h"
#include "WorldRenderer.h"
#include "SFMLRenderer.h"
#include "BlockRenderer.h"

class Camera;
class ChunkSection; 

class MasterRenderer {
public:
	MasterRenderer(const glm::mat4& proj);
	~MasterRenderer();

	void ProcessSFML(const sf::Drawable& draw);
	void ProcessChunkSection(ChunkSection& cs);
	void ProcessBreakAnim(const glm::vec3& pos, float p);
	void ProcessBlock(const glm::vec3& pos, ID id, bool invSlot = false);

	void Render(sf::RenderWindow& window, Camera& camera, float deltaTime);

	void RenderSkybox();

private:
	BreakAnimRenderer	breakAnimRenderer;
	SkyboxRenderer		skyboxRenderer;
	WorldRenderer		worldRenderer;
	SFMLRenderer		sfmlRenderer;
	BlockRenderer		blockRenderer;

	glm::mat4 projectionMatrix;
	bool renderSkybox = false;

	glm::vec3 bpos;
	int bindex = 0;
	bool bshouldRender = false;
	BasicShader bshader;

	GLuint bvao = 0;
	Texture btextures[BREAK_ANIM_CNT];

	CubeTexture texture;
	SkyboxShader sshader;
	GLuint svao;

	std::vector<Model> world, water, leave;	
	WorldShader worldShader;
	WaterShader waterShader;
	LeaveShader leaveShader;
};

