#include "Guard.h"

Guard::Guard(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos):
    Person(window, entities, walls, spawnPos, GRID_TYPE::GUARD, 0, "enemy_sprite.png")
{ }