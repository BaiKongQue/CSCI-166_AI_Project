#include "Object.h"

Object::Object(Window* window,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	Entity(window, walls, spawnPos, type, numberFrames, spritePath)
{}