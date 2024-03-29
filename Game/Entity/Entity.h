#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "../Display/Window.h"
#include "../Enum/GridType.enum.h"
#include "../Enum/State.enum.h"
#include <functional>

class Entity {
protected:
	Window* window;
	std::vector<int>* walls;
	std::vector<Entity*>* entities;
	SDL_Texture* spriteTexture;
	struct State {
		STATE state;
		int pos;
		std::function<void()> action;
		std::function<int()> reward;
	};
private:
	int numFrames;
	int currFrame;
	int frameRate;
	int oldTime;
	SDL_Rect* srcRect;
	SDL_Rect* destRect;
public:
    bool dead;
	GRID_TYPE type;
public:
	static std::vector<SDL_Texture*> spriteCache;
	int posX;
	int posY;
public:
	Entity(Window* window,
		std::vector<Entity*>* entities,
		std::vector<int>* walls,
		int spawnPos,
		GRID_TYPE type,
		int numberFrames,
		const char* spritePath);
private:
	void OnAnimate();
protected:
	bool IsWall(int pos);
	bool IsWall(int x, int y);
	virtual void OnCollision(Entity* entity);
public:
	virtual float GetReward(GRID_TYPE entityType);
	virtual void MakeMove();
	virtual void OnLoop();
	void OnRender();
	int GetPos(int x, int y);
	int GetX(int pos);
	int GetY(int pos);
public:
	~Entity();
};

#endif /* ENTITY_H */