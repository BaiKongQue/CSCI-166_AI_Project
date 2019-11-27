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

void Entity::OnLoop() {
    
}

void Entity::OnRender() {

}

void Entity::OnMove(int newX, int newY) {

}

void Entity::OnAnimate() {

}

void Entity::CanMove() {

}

void Entity::LoadImage() {

}

void Entity::OnCollision() {

}