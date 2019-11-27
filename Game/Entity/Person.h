#pragma once
#ifndef Person_H
#define Person_H

#include "Entity.h"
#include "AI.h"

class Person : Entity, AI {
public:
	Person();
private:
	void die();
public:
	~Person();
};

#endif /* Person_H */