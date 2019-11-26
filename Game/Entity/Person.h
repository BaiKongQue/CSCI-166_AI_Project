#ifndef Person_H
#define Person_H

#include "Entity.h"
#include "AI.h"

class Person : Entity, AI {
public:
    Person();
private:
    void die();
}

#endif /* Person_H */
