#include "UtilityFunctions.h"

#include "defines.h"
#include "Math/Vector2.h"

bool outOfChunkRange(int index) {
	return index >= CHUNK_SIZE || index < 0;
}

Vector2 chunkCoord(int x, int z) {

	Vector2 vec{ x / CHUNK_SIZE, z / CHUNK_SIZE };

	if (x < 0)
		vec.x -= 1;

	if (z < 0)
		vec.z -= 1;

	return vec;
}

Vector2 blockCoord(int x, int z) {

	Vector2 vec{ x % CHUNK_SIZE, z % CHUNK_SIZE };

	if (vec.x < 0)
		vec.x += CHUNK_SIZE;

	if (vec.z < 0)
		vec.z += CHUNK_SIZE;

	return vec;
}

Vector2 chunkCoord(float x, float z) {

	return chunkCoord((int)x, (int)z);
}

Vector2 blockCoord(float x, float z) {

	return blockCoord((int)x, (int)z);
}
