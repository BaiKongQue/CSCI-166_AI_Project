#include "Player.h"

Player::Player(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos):
    Person(window, entities, walls, spawnPos, GRID_TYPE::PLAYER, 0, "archer_sprite.png"),
	arrows(0),
	isArrowNocked(false)
{ }