#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h";

class Player : public Person {
private:
	int arrows;
	bool isArrowNocked;
public:
	Player(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
private:
	void PickUpArrow();
protected:
	virtual std::vector<Entity::State*>* AddStates();
public:
	void NockArrow();
	void FireArrow();
	float GetReward(GRID_TYPE entityType);
public:
	~Player();
};

#endif /* PLAYER_H */