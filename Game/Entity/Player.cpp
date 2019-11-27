#include "Player.h"

Player::Player(Window* window, std::vector<int>* walls, int spawnPos):
    Person(window, walls, spawnPos, GRID_TYPE::PLAYER, 0, nullptr),
	arrows(0),
	isArrowNocked(false)
{ }