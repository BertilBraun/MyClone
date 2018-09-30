#pragma once

struct Vector2;

bool outOfChunkRange(int index);

bool isOutOfTotalRange(int x, int y, int z);

Vector2 chunkCoord(int x, int z);

Vector2 blockCoord(int x, int z);

Vector2 chunkCoord(float x, float z);

Vector2 blockCoord(float x, float z);