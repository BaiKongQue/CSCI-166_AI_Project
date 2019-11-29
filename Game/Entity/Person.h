#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"
#include "AI.h"

class Person : public Entity, protected AI {
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
public:
	~Person();
};

#endif /* Person_H */