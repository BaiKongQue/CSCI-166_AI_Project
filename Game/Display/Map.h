#pragma once
#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <fstream>
#include <string>
#include <vector>

#include "Display.h"
#include "Window.h"
#include "../Entity/Entity.hpp"
#include "../Entity/Person.hpp"
#include "../Entity/Arrow.hpp"
#include "../Entity/Treasure.hpp"

class Map : Display {
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