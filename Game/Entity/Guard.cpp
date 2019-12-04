#include "Guard.h"

float* Guard::vGrid = nullptr;

Guard::Guard(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos):
    Person(window, entities, walls, spawnPos, GRID_TYPE::GUARD, 8, "enemy_sprite.png")
{
	if (Guard::vGrid == nullptr) {
		Guard::vGrid = new float[this->window->gridSizeX * this->window->gridSizeY];
		for (int i = 0; i < this->window->gridSizeX * this->window->gridSizeY; i++) {
			Guard::vGrid[i] = 1;
		}
	}
}

float Guard::GetReward(GRID_TYPE entityType) {
	switch (entityType) {
	case GRID_TYPE::PLAYER: return -10; break;
	default: return 1; break;
	}
}

float* Guard::GetVGrid() {
	return Guard::vGrid;
}