#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "../Display/Display.h"

class Entity {
protected:
	GRID_TYPE type;
	int pos;
	int numFrames;
	int currFrame;
	SDL_Texture* spriteTexture;
protected:
	Display* display;
	Window* window;
public:
	Entity(Display* display, Window* window, const GRID_TYPE type, int spawnPos, const int numberFrames, const char* spriteLocation);
public:
	void OnLoop();
	void OnRender();
protected:
	void OnMove(int newX, int newY);
	void OnAnimate();
	void CanMove();
	void LoadImage();
	void OnCollision(Entity* entity);
public:
	~Entity();
};

#endif /* ENTITY_H */