#include "Arrow.h"

Arrow::Arrow(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos) :
	Object(window, entities, walls, spawnPos, GRID_TYPE::ARROW, 1, "")
{}

float Arrow::GetReward(GRID_TYPE entityType) {
	switch (entityType) {
	case GRID_TYPE::PLAYER: return 5; break;
	default: return 0; break;
	}
}