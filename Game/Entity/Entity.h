#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "../Display/Window.h"
#include "../Enum/GridType.enum.h"

class Entity {
protected:
	GRID_TYPE type;
	int pos;
	int numFrames;
	int currFrame;
	SDL_Texture* spriteTexture;
public:
	Entity();
public:
	void OnLoop();
	void OnRender();
	void OnCleanup();
protected:
	void OnMove(int newX, int newY);
	void OnAnimate();
	void CanMove();
	void LoadImage();
	void OnCollision(Entity* entity);
};

#endif /* ENTITY_H */