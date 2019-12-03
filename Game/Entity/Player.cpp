#include "Player.h"

Player::Player(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos):
    Person(window, entities, walls, spawnPos, GRID_TYPE::PLAYER, 4, "archer_sprite.png"),
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
	if (this->arrows > 0) {
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
					Entity* target = nullptr;

					while (target == nullptr
						&& (x >= 0 && x < this->window->gridSizeX)
						&& (y >= 0 && y < this->window->gridSizeY)
						&& (!this->IsWall(x, y))
					) {
						for (Entity* entity : *this->entities) {
							if (entity->type == GRID_TYPE::GUARD && entity->posX == x && entity->posY == y) {
								target = entity;
								break;
							}
						}
						x += i;
						y += j;
					}

					if (target != nullptr) {
						states->push_back(new Entity::State{
							STATE::FIRE_ARROW,
							(target->GetPos(target->posX, target->posY)),
							[=]()->void {
								for (int i = 0; i < this->entities->size(); i++) {
									if (this->entities->at(i) == target) {
										this->entities->erase(this->entities->begin() + i);
										delete target;
										return;
									}
								}
							},
							[=]()->int {
								return 1;
							}
						});
					}
				}
			}
		}
	}
	return states;
}

void Player::OnCollision(Entity* entity) {
	switch (entity->type) {
	case GRID_TYPE::ARROW:
		this->arrows++;
		for (int i = 0; i < this->entities->size(); i++) {
			if (this->entities->at(i) == entity) {
				this->entities->erase(this->entities->begin() + i);
				delete entity;
				return;
			}
		}
		break;
	case GRID_TYPE::GUARD:
		this->dead = true;
		break;
	}
}
