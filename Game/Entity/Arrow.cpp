#include "Arrow.h"

Arrow::Arrow(Window* window, std::vector<int>* walls, int spawnPos) :
	Object(window, walls, spawnPos, GRID_TYPE::ARROW, 1, "")
{}