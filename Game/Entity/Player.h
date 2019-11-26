#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h";

class Player : Person {
private:
	int arrows;
	bool isArrowNocked;
public:
	Player();
private:
	void PickUpArrow();
public:
	void NockArrow();
	void FireArrow();
};

#endif /* PLAYER_H */