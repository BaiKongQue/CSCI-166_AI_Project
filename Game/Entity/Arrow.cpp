#include "Arrow.h"

Arrow::Arrow(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos) :
	Object(window, entities, walls, spawnPos, GRID_TYPE::ARROW, 1, "")
{}