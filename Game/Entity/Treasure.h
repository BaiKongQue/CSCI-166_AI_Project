#pragma once
#ifndef Treasure_H
#define Treasure_H

#include "Object.h"

class Treasure : public Object {
public:
    Treasure(int spawnPos);
	~Treasure();
};

#endif /* Treasure_H */
