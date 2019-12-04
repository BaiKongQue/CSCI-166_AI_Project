#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"
#include <iterator>
#include <random>
#include <tuple>

class Person : public Entity {
private:
	int vSize;
	float* vk_1;
	float* vk;
	float gamma;
	std::random_device seeder;
	std::mt19937 engine;
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
	std::vector<Entity::State*>* GetStates(int pos);
	float Equation(Entity::State* state, std::vector<Entity::State*>* states);
	void Bellmans();
	void MaxState();
public:
	virtual void MakeMove();
public:
	~Person();
};

#endif /* Person_H */