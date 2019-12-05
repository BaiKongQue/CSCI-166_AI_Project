#include "Guard.h"

float* Guard::vk = nullptr;
bool Guard::canCalculate = true;
int Guard::count = 0;

Guard::Guard(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos) :
	Person(window, entities, walls, spawnPos, GRID_TYPE::GUARD, 8, "enemy_sprite.png")
{
	this->LoadVk();
	Guard::count++;
}

float Guard::GetReward(GRID_TYPE entityType) {
	switch (entityType) {
	case GRID_TYPE::PLAYER: return -10; break;
	case GRID_TYPE::GUARD: return -0.1; break;
	default: return 0; break;
	}
}

float* Guard::GetVk() {
	return Guard::vk;
}

int Guard::GetIterNum() {
	return 10;
}

void Guard::MakeMove() {
	if (Guard::canCalculate)
		this->Bellmans();
	this->MaxState();
}