#include "Treasure.h"

Treasure::Treasure(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos) :
	Object(window, entities, walls, spawnPos, GRID_TYPE::TREASURE, 1, "treasure_sprite.png")
{}

float Treasure::GetReward(GRID_TYPE entityType) {
	switch (entityType) {
	case GRID_TYPE::PLAYER: return 100; break;
	default: return 0; break;
	}
}

void Treasure::OnCollision(Entity* entity) {
	switch (entity->type) {
	case GRID_TYPE::PLAYER: this->dead = true; break;
	}
}