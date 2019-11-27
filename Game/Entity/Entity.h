#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "../Display/Window.h"
#include "../Enum/GridType.enum.h"

class Entity {
protected:
	int type;
	int pos;
	int numFrames;
	int currFrame;
	SDL_Texture* spriteTexture;
protected:
	Window* window;
	std::vector<int>* walls;
public:
	Entity(Window* window,
		std::vector<int>* walls,
		int spawnPos,
		GRID_TYPE type,
		int numberFrames,
		const char* spritePath);
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