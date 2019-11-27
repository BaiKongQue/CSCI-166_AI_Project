#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"
#include "AI.h"

class Person : public Entity, protected AI {
public:
	Person(int spawnPos);
private:
	void die();
public:
	~Person();
};

#endif /* Person_H */