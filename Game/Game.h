#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity/Entity.h"
#include "Display/Display.h"

class Game {
private:
	bool running;		// if the game is running
	bool gameWon;		// if the game is won
	SDL_Event events;
private:
	Window* window;
	Display* display;
	std::vector<Entity*>* entities;
public:
	Game();
private:
	void OnInit();
	void OnLoop();
	void OnRender();
public:
	void Run();
public:
	~Game();
};

#endif /* GAME_H */