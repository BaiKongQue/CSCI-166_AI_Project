#include "Entity.h"

Entity::Entity(Display* display, Window* window, const GRID_TYPE type, int spawnPos, const int numberFrames, const char* spritePath) :
	display(display),
	window(window),
	type(type),
	pos(spawnPos),
	numFrames(numberFrames),
	currFrame(0),
	spriteTexture(nullptr)
{
	this->spriteTexture = this->window->LoadImageTexture(spritePath);
}