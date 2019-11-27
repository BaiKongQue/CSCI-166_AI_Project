#include "Person.h"

Person::Person(Window* window,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	Entity(window, walls, spawnPos, type, numberFrames, spritePath),
	AI()
{}