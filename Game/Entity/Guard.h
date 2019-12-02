#pragma once
#ifndef GUARD_H
#define GUARD_H

#include "Person.h"

class Guard : public Person {
public:
	Guard(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
	~Guard();
public:
	float GetReward(GRID_TYPE entityType);

};

#endif /* GUARD_H */