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

	if (Entity::spriteCache[(type - 1)] == nullptr) {
		std::string path = "./Assets/images/";
		path += spritePath;
		Entity::spriteCache[(type - 1)] = this->window->LoadImageTexture(path.c_str());
	}
	this->spriteTexture = Entity::spriteCache[(type - 1)];
}

void Entity::OnAnimate() {
	if (this->oldTime + this->frameRate > SDL_GetTicks())
		return;

	this->oldTime = SDL_GetTicks();
	this->currFrame += 1;

	if (this->currFrame >= this->numFrames)
		this->currFrame = 0;
}

bool Entity::IsWall(int x, int y) {
	int newPos = this->GetPos(x, y);
	for (int i : *this->walls) {
		if (newPos > i)
			break;
		if (newPos == i)
			return false;
	}

	return true;
}

std::vector<Entity::State*>* Entity::GetStates() {
	std::vector<Entity::State*>* states = new std::vector<Entity::State*>();

	// retrieve all states
	for (int i : {-1, 0, 1}) {
		for (int j : { -1, 0, 1 }) {
			int x = i + this->posX;
			int y = j + this->posY;
			int pos = x + (y * (this->window->gridSizeX));
			if (
				((i == 0) != (j == 0))
				&& (x >= 0 && x < this->window->gridSizeX)
				&& (y >= 0 && y < this->window->gridSizeY)
				&& (!this->IsWall(x, y))
			) {
				STATE direction = (i == 0 && j == -1) ? STATE::NORTH :
					(i == 1 && j == 0) ? STATE::EAST :
					(i == 0 && j == 1) ? STATE::SOUTH :
					STATE::WEST;
				states->push_back(new Entity::State{ direction, [this](){
					this->posX = x;
					this->posY = y;
				}});
			}
		}
	}

	return states;
}

void Entity::OnLoop() {
	this->OnAnimate();
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

	this->window->Draw(this->spriteTexture, destRect, srcRect);

	delete srcRect;
	delete destRect;
}

int Entity::GetX(int pos) {
	return pos / this->window->gridSizeX;
}

int Entity::GetY(int pos) {
	return pos % this->window->gridSizeX;
}

int Entity::GetPos(int x, int y) {
	return x + (y * this->window->gridSizeX);
}

Entity::~Entity() {
	this->numFrames = 0;
	this->currFrame = 0;
	this->frameRate = 0;
	this->oldTime = 0;
	this->dead = false;
	this->spriteTexture = nullptr;
}