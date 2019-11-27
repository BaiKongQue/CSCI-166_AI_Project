#include "Entity.h"

Entity::Entity(Window* window,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	window(window),
	walls(walls),
	type(type),
	pos(spawnPos),
	numFrames(numberFrames),
	currFrame(0),
	spriteTexture(nullptr)
{
	this->spriteTexture = this->window->LoadImageTexture(spritePath);
}