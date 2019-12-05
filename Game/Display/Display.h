#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL.h>
#include <fstream>
#include <string>
#include <vector>

#include "../Entity/Entity.h"
#include "../Entity/Player.h"
#include "../Entity/Guard.h"
#include "../Entity/Arrow.h"
#include "../Entity/Treasure.h"
#include "../Enum/GridType.enum.h"
#include "Window.h"


class Display {
private:
    Window* window;
    std::string currLevel;
    SDL_Texture* levelMsgTexture;
    SDL_Texture* grassTexture;
    SDL_Texture* wallTexture;
    std::vector<int>* walls;
	SDL_Rect* currRect;
public:
    Display(Window*);
public:
	std::vector<int>* GetWalls();
	void AddWall(int pos);
	void ClearWalls();
public:
    void OnRender();
public:
    ~Display();
};

#endif /* DISPLAY_H */