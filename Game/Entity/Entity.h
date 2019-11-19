#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "AI.h"
#include "../Display/Window.h"
#include "../Enum/GridType.enum.h"

class Entity : AI {
protected:
	bool dead;
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
	void OnMove(int newX, int newY);
	void OnCleanup();
protected:
	void MakeMove();
	void OnAnimate();
	void CanMove();
	void LoadImage();
};

#endif /* ENTITY_H */