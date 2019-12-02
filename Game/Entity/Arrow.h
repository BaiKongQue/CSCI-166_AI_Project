#pragma once
#ifndef Arrow_H
#define Arrow_H

#include "Object.h"

class Arrow : public Object {
public:
    Arrow(Window* window, std::vector<Entity*>* entities, std::vector<int>* walls, int spawnPos);
	~Arrow();
};

#endif /* Arrow_H */