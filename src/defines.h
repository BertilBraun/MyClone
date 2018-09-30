#pragma once

#define INFO_FILE_PATH "res/saves/worldsInfos.txt"

#define DIG_TIME 0.3f
#define DIG_DISTANCE 6

#define MAX_HP 20

#define BREAK_ANIM_CNT 10

#define JUMP_POWER 3.5f
#define GRAVITY glm::vec3(0, 9.0f, 0)

#define LIGHT_TOP 1.0f
#define LIGHT_SIDE 0.7f
#define LIGHT_DOWN 0.3f

#define LIGHT_MAX 15

#define Z_NEAR 0.001f
#define Z_FAR 1000.0f

#define SKYBOX_SIZE 500.0f

#define CHUNK_SIZE 16
#define CHUNK_AREA (CHUNK_SIZE * CHUNK_SIZE)
#define CHUNK_VOLUME (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)

#define WATERLEVEL 60

#define STEP_SIZE 0.01f

#include "GL/glew.h"
#include <iostream>

#define MUTEX(x, y) x.lock(); y; x.unlock();

//#define TRY(x)	x;

#define TRY(x)		try { x; } catch(std::exception& e) { std::cout << e.what() << " WAS THROWN BY EXCEPTION\n"; __debugbreak(); }

#define ASSERT(x)	if(!(x))\
						__debugbreak();
//#define GLCall(x)	x;

#define GLCall(x)	{\
						for (GLuint i = 0; glGetError() != GL_NO_ERROR && i < 50; i++);\
						x;\
						ASSERT(!glGetError());\
					}
