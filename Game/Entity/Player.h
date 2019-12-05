#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h";

class Player : public Person {
private:
	int arrows;
	static float* vk;
public:
	Player(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
protected:
	std::vector<Entity::State*>* AddStates(int pos);
	void OnCollision(Entity* arrow);
	float* GetVk();
public:
	float GetReward(GRID_TYPE entityType);
public:
	~Player();
};

#endif /* PLAYER_H */