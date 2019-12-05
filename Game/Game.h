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
	int currLevel;
private:
	Window* window;
	Display* display;
	std::vector<Entity*>* entities;
public:
	Game();
private:
	void LoadLevel(std::string level);
	void ClearGame();
private:
	void OnInit();
	void OnLoop();
	void OnRender();
	void WinCondition();
public:
	void Run();
public:
	~Game();
};

#endif /* GAME_H */