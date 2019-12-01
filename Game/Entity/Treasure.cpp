#include "Treasure.h"

Treasure::Treasure(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos) :
	Object(window, entities, walls, spawnPos, GRID_TYPE::TREASURE, 1, "teasure_sprite.png")
{}