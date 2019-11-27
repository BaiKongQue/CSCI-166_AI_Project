#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h";

class Player : public Person {
private:
	int arrows;
	bool isArrowNocked;
public:
	Player(Window* window, std::vector<int>* walls, stdint spawnPos);
private:
	void PickUpArrow();
public:
	void NockArrow();
	void FireArrow();
public:
	~Player();
};

#endif /* PLAYER_H */