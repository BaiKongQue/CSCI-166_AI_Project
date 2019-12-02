#pragma once
#ifndef Treasure_H
#define Treasure_H

#include "Object.h"

class Treasure : public Object {
public:
    Treasure(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
	~Treasure();
public:
	float GetReward(GRID_TYPE entityType);

};

#endif /* Treasure_H */
