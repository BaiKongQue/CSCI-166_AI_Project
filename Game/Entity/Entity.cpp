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
	spriteTexture(nullptr),
	srcRect(new SDL_Rect{ 0, 0, this->window->bitSize, this->window->bitSize }),
	destRect(new SDL_Rect{ 0, 0, this->window->bitSize, this->window->bitSize })
{
	// if sprite cache is empty initialize it
	if (Entity::spriteCache.empty()) {
		for (int i = 0; i < 4; i++) {
			Entity::spriteCache.push_back(nullptr);
		}
	}

	// get sprite from sprite cache if not exist add it
	if (Entity::spriteCache[(type - 2)] == nullptr) {
		std::string path = "./Assets/images/";
		path += spritePath;
		Entity::spriteCache[(type - 2)] = this->window->LoadImageTexture(path.c_str());
	}
	this->spriteTexture = Entity::spriteCache[(type - 2)];


}

void Entity::OnAnimate() {
	if (this->numFrames <= 0 || this->oldTime + this->frameRate > SDL_GetTicks())
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
			return true;
	}

	return false;
}

std::vector<Entity::State*>* Entity::GetStates() {
	std::vector<Entity::State*>* states = new std::vector<Entity::State*>();

	// retrieve all states
	for (int i : {-1, 0, 1}) {
		for (int j : { -1, 0, 1 }) {
			int x = i + this->posX;
			int y = j + this->posY;

			if (
				((i == 0) != (j == 0))
				&& (x >= 0 && x < this->window->gridSizeX)
				&& (y >= 0 && y < this->window->gridSizeY)
				&& (!this->IsWall(x, y))
			) {
				STATE state = (i == 0 && j == -1) ? STATE::NORTH :
					(i == 1 && j == 0) ? STATE::EAST :
					(i == 0 && j == 1) ? STATE::SOUTH :
					STATE::WEST;
				states->push_back(new Entity::State{
					state,
					[=]()->void {
						this->posX = x;
						this->posY = y;
					},
					[=]()->int {
						for (Entity* entity : *this->entities) {
							if (entity->posX == x && entity->posY == y)
								return entity->GetReward(this->type);
						}
						return 1;
					}
				});
			}
		}
	}

	return states;
}

void Entity::MakeMove() {}
void Entity::OnCollision(GRID_TYPE entityType) {}
float Entity::GetReward(GRID_TYPE entityType) { return 0; }

void Entity::OnLoop() {
	this->OnAnimate();
}

void Entity::OnRender() {
	this->srcRect->x = this->currFrame * this->window->bitSize;

	this->destRect->x = this->posX * this->window->bitSize;
	this->destRect->y = this->posY * this->window->bitSize;

	this->window->Draw(this->spriteTexture, this->destRect, this->srcRect);
}

int Entity::GetX(int pos) {
	return pos % this->window->gridSizeX;
}

int Entity::GetY(int pos) {
	return pos / this->window->gridSizeX;
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
	delete this->srcRect;
	delete this->destRect;
}