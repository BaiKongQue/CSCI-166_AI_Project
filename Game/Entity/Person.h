#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"
#include <iterator>
#include <random>

class Person : public Entity {
private:
	int vSize;
	float* vk_1;
	float* vk;
	float gamma;
	std::random_device seeder;
	std::mt19937 engine;
	float* vtest;
public:
	Person(Window* window,
		std::vector<Entity*>* entities,
		std::vector<int>* walls,
		int spawnPos,
		GRID_TYPE type,
		int numberFrames,
		const char* spritePath);
protected:
	virtual std::vector<Entity::State*>* AddStates();
private:
	float Equation(Entity::State* state, std::vector<Entity::State*>* states);
	void Bellmans();
	Entity::State* MaxState(float* ar, std::vector<Entity::State*>* states);
public:
	void MakeMove();
public:
	~Person();
};

#endif /* Person_H */