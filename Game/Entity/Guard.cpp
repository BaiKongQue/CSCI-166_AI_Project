#include "Guard.h"

Guard::Guard(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos):
    Person(window, entities, walls, spawnPos, GRID_TYPE::GUARD, 8, "enemy_sprite.png")
{ }

float Guard::GetReward(GRID_TYPE entityType) {
	switch (entityType) {
	case GRID_TYPE::PLAYER: return -10; break;
	default: return 0; break;
	}
}