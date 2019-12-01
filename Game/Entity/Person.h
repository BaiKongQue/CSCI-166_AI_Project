#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"

class Person : public Entity {
public:
	Person(Window* window,
		std::vector<Entity*>* entities,
		std::vector<int>* walls,
		int spawnPos,
		GRID_TYPE type,
		int numberFrames,
		const char* spritePath);
private:
	void die();
protected:
	virtual bool CanMove(int newX, int newY);
	virtual void OnMove(int newX, int newY);
	void MakeMove();
private:
	float Equation(int* vk_1, Entity::State* state);
	int Bellmans();
protected:
	virtual std::vector<Entity::State*>* AddStates();
public:
	~Person();
};

#endif /* Person_H */