#include "Player.h"

#include "defines.h"
#include "SFML/Graphics.hpp"

#include "Entity.h"
#include "Camera.h"

#include "World/World.h"
#include "Application.h"

#include "Utils/ToggleKey.h"
#include "Utils/UtilityFunctions.h"

#include "Renderer/MasterRenderer.h"
#include <sstream>

Player::Player(WorldInfo& info, World* world, Application* app) :
	MoveEntity({ 0.8, 1.2, 0.8 }),
	text(DataBase::get().getText()),
	inventory(app, info.path, 36, 9),
	world(world)
{
	text.move(10, 35);

	if (info.setPosition)
		pos = world->getSpawnPoint();
	else {
		pos = info.pos;

		Vector2 c = chunkCoord(pos.x, pos.z);
		Vector2 b = blockCoord(pos.x, pos.z);

		world->LoadChunk(c.x, c.z);

		if (b.x == 0)
			world->LoadChunk(c.x - 1, c.z);
		else if (b.x == CHUNK_SIZE - 1)
			world->LoadChunk(c.x + 1, c.z);

		if (b.z == 0)
			world->LoadChunk(c.x, c.z - 1);
		else if (b.z == CHUNK_SIZE - 1)
			world->LoadChunk(c.x, c.z + 1);
		
		if (collision(world, pos))
			pos = world->getSpawnPoint();

		world->setSpawnPointSet(true);
	}

	hpTex.reserve(MAX_HP / 2);
	noHpTex.reserve(MAX_HP / 2);
	for (int i = 0; i < MAX_HP / 2; i++) {
		hpTex.emplace_back(glm::vec2(0), glm::vec2(0.02, 0.023), "GUI/health.png", (*app->getWindow()));
		noHpTex.emplace_back(glm::vec2(0), glm::vec2(0.02, 0.023), "GUI/noHealth.png", (*app->getWindow()));
		hpTex[i].setPos(glm::vec2(0.27 + i * 0.023, 0.85), (*app->getWindow()));
		noHpTex[i].setPos(glm::vec2(0.27 + i * 0.023, 0.85), (*app->getWindow()));
	}
}


Player::~Player() {
}

void Player::KeyboardInput(const Camera& cam) {
	
	inventory.Update();

	sprinting = (	sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || 
					sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));

	glm::vec3	forward = cam.forward,
				right	= cam.right;

	forward.y = 0;
	right.y = 0;

	forward  = glm::normalize(forward);
	right    = glm::normalize(right);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		if (sprinting && onGround)
			vel += forward * 1.5f;
		else
			vel += forward * 1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
		vel -= forward;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		vel += right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		vel -= right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (onGround) {
			vel.y = JUMP_POWER;
			onGround = false;
		}
		else if (swimming)
			vel.y = JUMP_POWER * 0.3f;
	}

	if (health <= 0) {
		world->saveAll();
		exit(0);
		//JUST DONT DIE!
		pos = world->getSpawnPoint();
		health = MAX_HP;
		vel = glm::vec3(0);
	}
}

void Player::DisplayInformation(MasterRenderer& renderer, const Camera& cam, Application* app) {

	char s[4096];

	sprintf_s(s, "%.2f x : %.2f y : %.2f z : FH : OnGround %i\n", pos.x, pos.y, pos.z, onGround);
	sprintf_s(s, "%s%.2f x : %.2f y : %.2f z : SH\n", s, pos.x, pos.y - 1.3f, pos.z);
	sprintf_s(s, "%s%.2f x : %.2f y : %.2f z\n", s, cam.forward.x, cam.forward.y, cam.forward.z);

	sprintf_s(s, "%s%s", s, world->getBiome(pos.x, pos.z).name.c_str());

	text.setString(s);
	renderer.ProcessSFML(text);

	for (int i = 0; i < MAX_HP / 2; i++)
		noHpTex[i].draw(renderer);

	for (int i = 0; i < health / 2; i++) 
		hpTex[i].draw(renderer);
	
	inventory.render(renderer);
}

bool Player::removeOneFromHand() {

	if (inventory.currSlot().type != SlotType::BLOCK)
		return false;

	return inventory.tryToRemove(inventory.currSlot().block->id, 1);
}

ChunkBlock Player::getHeldBlock() {

	Slot& s = inventory.currSlot();

	if (s.type != SlotType::BLOCK)
		return ID::Air;

	return s.getStackSize() <= 0 ? ID::Air : s.block->id;
}

Slot & Player::getCurrSlot() {

	return inventory.currSlot();
}

Inventory & Player::getInventory() {
	return inventory;
}