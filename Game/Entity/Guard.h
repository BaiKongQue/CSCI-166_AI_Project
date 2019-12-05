#pragma once
#ifndef GUARD_H
#define GUARD_H

#include "Person.h"

class Guard : public Person {
private:
	static float* vk;
public:
	static bool canCalculate;
	static int count;
public:
	Guard(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
	~Guard();
protected:
	float* GetVk();
	int GetIterNum();
public:
	float GetReward(GRID_TYPE entityType);
	void MakeMove();

};

#endif /* GUARD_H */