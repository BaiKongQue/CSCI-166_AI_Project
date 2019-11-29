#include "Entity.h"

std::vector<SDL_Texture*> Entity::spriteCache;

Entity::Entity(Window* window,
	std::vector<Entity*>* entities,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	window(window),
	entities(entities),
	walls(walls),
	type(type),
	posX(this->GetX(spawnPos)),
	posY(this->GetY(spawnPos)),
	numFrames(numberFrames),
	currFrame(0),
	frameRate(100),
	oldTime(0),
	dead(false),
	spriteTexture(nullptr)
{
	if (Entity::spriteCache.empty()) {
		for (int i = 0; i < 4; i++) {
			Entity::spriteCache.push_back(nullptr);
		}
	}

	if (Entity::spriteCache[type - 1] == nullptr) {
		std::string path = "./Assets/images/";
		path += spritePath;
		Entity::spriteCache[type - 1] = this->window->LoadImageTexture(path.c_str());
	}
	this->spriteTexture = Entity::spriteCache[type - 1];
}

void Entity::OnLoop() {
	//this->OnAnimate();
}

void Entity::OnRender() {
	SDL_Rect* srcRect = new SDL_Rect();
	srcRect->w = this->window->bitSize;
	srcRect->h = this->window->bitSize;
	srcRect->x = this->currFrame * this->window->bitSize;
	srcRect->y = 0;

	SDL_Rect* destRect = new SDL_Rect();
	destRect->w = this->window->bitSize;
	destRect->h = this->window->bitSize;
	destRect->x = this->posX * this->window->bitSize;
	destRect->y = this->posY * this->window->bitSize;

	this->window->Draw(this->spriteTexture, *srcRect, *destRect);

	delete srcRect;
	delete destRect;
}

bool Entity::IsDead() {
	return this->dead;
}

GRID_TYPE Entity::GetType() {
	return this->type;
}

int Entity::GetPos() {
	return this->posX + (this->posY * this->window->gridSizeX);
}

void Entity::OnMove(int newX, int newY) {

}

void Entity::OnAnimate() {
	if (this->oldTime + this->frameRate > SDL_GetTicks())
		return;

	this->oldTime = SDL_GetTicks();
	this->currFrame += 1;

	if (this->currFrame >= this->numFrames)
		this->currFrame = 0;
}

bool Entity::CanMove(int newPos) {
	for (int i : *this->walls) {
		if (newPos == i) 
			return false;
	}

	for (Entity* entity : *this->entities) {
		if (entity->GetType() == GRID_TYPE::GUARD && entity->GetPos() == newPos)
			return false;
	}

	return true;
}

void Entity::OnCollision(Entity* entity) {

}

int Entity::GetX(int pos) {
	return pos / this->window->gridSizeX;
}

int Entity::GetY(int pos) {
	return pos % this->window->gridSizeX;
}

Entity::~Entity() {

}