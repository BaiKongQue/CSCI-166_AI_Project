#include "Person.h"

Person::Person(Window* window,
	std::vector<Entity*>* entities,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	Entity(window, entities, walls, spawnPos, type, numberFrames, spritePath),
	AI()
{}