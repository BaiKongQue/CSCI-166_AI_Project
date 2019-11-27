#pragma once
#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <fstream>
#include <string>
#include <vector>

#include "Display.h"
#include "Window.h"
#include "../Entity/Entity.h"
#include "../Entity/Person.h"
#include "../Entity/Arrow.h"
#include "../Entity/Treasure.h"

class Map : public Display {
private:
    std::string currLevel;
    SDL_Texture* levelMsgTexture;
    SDL_Texture* grassTexture;
    SDL_Texture* wallTexture;

    std::vector<int> walls;
    std::vector<Entity*> entities;

public:
    Map(Window* window);
private:
    void LoadLevel(std::string level);
    void OnRender();
};

#endif /* MAP_H */