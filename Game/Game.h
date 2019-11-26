#pragma once
#ifndef GAME_H
#define GAME_H

class Game {
private:
	bool running;		// if the game is running
	bool gameWon;		// if the game is won
public:
	Game();
	~Game();
private:
	void OnInit();
	void OnLoop();
	void OnRender();
	void OnCleanup();
	void OnExit();
public:
	void Run();

};

#endif /* GAME_H */