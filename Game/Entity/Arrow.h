#pragma once
#ifndef Arrow_H
#define Arrow_H

#include "Object.h"

class Arrow : public Object {
public:
    Arrow(int spawnPos);
	~Arrow();
};

#endif /* Arrow_H */