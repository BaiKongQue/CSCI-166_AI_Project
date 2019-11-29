#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "../Display/Window.h"
#include "../Enum/GridType.enum.h"

class Entity {
protected:
	Window* window;
	std::vector<int>* walls;
	std::vector<Entity*>* entities;
private:
	int numFrames;
	int currFrame;
	int frameRate;
	int oldTime;
protected:
    bool dead;
	GRID_TYPE type;
	int posX;
	int posY;
	SDL_Texture* spriteTexture;
public:
	static std::vector<SDL_Texture*> spriteCache;
public:
	Entity(Window* window,
		std::vector<Entity*>* entities,
		std::vector<int>* walls,
		int spawnPos,
		GRID_TYPE type,
		int numberFrames,
		const char* spritePath);
public:
	virtual void OnLoop();
	void OnRender();
    bool IsDead();
	GRID_TYPE GetType();
	int GetPos();
protected:
	virtual bool CanMove(int newPos);
	virtual void OnMove(int newX, int newY);
	virtual void OnCollision(Entity* entity);
	void OnAnimate();
	int GetX(int pos);
	int GetY(int pos);
public:
	~Entity();
};

#endif /* ENTITY_H */