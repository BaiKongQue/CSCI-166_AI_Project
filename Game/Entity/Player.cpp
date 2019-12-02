#include "Player.h"

Player::Player(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos):
    Person(window, entities, walls, spawnPos, GRID_TYPE::PLAYER, 0, "archer_sprite.png"),
	arrows(0),
	isArrowNocked(false)
{ }

float Player::GetReward(GRID_TYPE entityType) {
	switch (entityType) {
	case GRID_TYPE::GUARD: return 10; break;
	default: return 0; break;
	}
}

std::vector<Entity::State*>* Player::AddStates() {
	std::vector<Entity::State*>* states = new std::vector<Entity::State*>();
	for (int i : {-1, 0, 1}) {
		for (int j : { -1, 0, 1 }) {
			int x = i + this->posX;
			int y = j + this->posY;

			if (
				((i == 0) != (j == 0))
				&& (x >= 0 && x < this->window->gridSizeX)
				&& (y >= 0 && y < this->window->gridSizeY)
				&& (!this->IsWall(x, y))
			) {

				states->push_back(new Entity::State{
					STATE::FIRE_ARROW,
					[=]()->void {
						
					},
					[=]()->int {

					}
				});
			}
		}
	}
}