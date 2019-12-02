#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"
#include <limits>

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
	virtual std::vector<Entity::State*>* AddStates();
private:
	float Equation(float* vk_1, Entity::State* state, std::vector<Entity::State*>* states);
	STATE Bellmans();
	STATE MaxState(float* ar, int size);
public:
	void MakeMove();
public:
	~Person();
};

#endif /* Person_H */