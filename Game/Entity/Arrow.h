#pragma once
#ifndef Arrow_H
#define Arrow_H

#include "Object.h"

class Arrow : public Object {
public:
    Arrow(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
	~Arrow();
public:
	float GetReward(GRID_TYPE entityType);

};

#endif /* Arrow_H */