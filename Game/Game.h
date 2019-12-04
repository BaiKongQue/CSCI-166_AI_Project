#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity/Entity.h"
#include "Display/Display.h"
#include <thread>
#include <chrono>

class Game {
private:
	bool running;		// if the game is running
	bool playerAlive;
	bool gameWon;		// if the game is won
	int turn;
private:
	Window* window;
	Display* display;
	std::vector<Entity*>* entities;
public:
	Game();
private:
	void LoadLevel(const char* level);
	void ClearGame();
private:
	void OnInit();
	void OnLoop();
	void OnRender();
public:
	void TakeTurn();
	void Run();
public:
	~Game();
};

#endif /* GAME_H */