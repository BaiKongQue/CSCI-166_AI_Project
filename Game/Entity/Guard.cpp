#include "Guard.h"

Guard::Guard(Window* window, std::vector<int>* walls, int spawnPos):
    Person(window, walls, spawnPos, GRID_TYPE::GUARD, 0, nullptr)
{ }