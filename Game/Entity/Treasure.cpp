#include "Treasure.h"

Treasure::Treasure(Window* window, std::vector<int>* walls, int spawnPos) :
	Object(window, walls, spawnPos, GRID_TYPE::TREASURE, 1, "")
{}