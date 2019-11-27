#pragma once
#ifndef Object_H
#define Object_H

#include "Entity.h"

class Object : public Entity {
public:
    Object(int spawnPos);
	~Object();
};

#endif /* Object_H */
