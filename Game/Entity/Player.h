#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h";

class Player : public Person {
private:
	int arrows;
	bool isArrowNocked;
	static float* vk;
public:
	Player(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
private:
	//bool guardInSight();
protected:
	virtual std::vector<Entity::State*>* AddStates(int pos);
	void OnCollision(Entity* arrow);
	float* GetVk();
public:
	float GetReward(GRID_TYPE entityType);
	//void MakeMove();
public:
	~Player();
};

#endif /* PLAYER_H */