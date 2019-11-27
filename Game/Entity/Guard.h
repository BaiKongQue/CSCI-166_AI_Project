#pragma once
#ifndef GUARD_H
#define GUARD_H

#include "Person.h"

class Guard : public Person {
public:
	Guard(Window* window, std::vector<int>* walls, int spawnPos);
	~Guard();
};

#endif /* GUARD_H */