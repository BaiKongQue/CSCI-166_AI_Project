#pragma once
#ifndef MAP_H
#define MAP_H

#include "Display.h"

class Map : Display {
private:
	std::string currLevel;
	SDL_Texture* levelMsgTexture;
	SDL_Texture* grassTexture;
	SDL_Texture* wallTexture;
	SDL_Texture* arrowTexture;
	SDL_Texture* treasureTexture;
public:
	Map();
private:
	void LoadLevel(std::string level);
};

#endif /* MAP_H */