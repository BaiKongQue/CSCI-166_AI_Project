#pragma once
#ifndef Object_H
#define Object_H

#include "Entity.h"

class Object : public Entity {
public:
    Object(Window* window,
		std::vector<Entity*>* entities,
		std::vector<int>* walls,
		int spawnPos,
		GRID_TYPE type,
		int numberFrames,
		const char* spritePath);
	~Object();
};

#endif /* Object_H */
