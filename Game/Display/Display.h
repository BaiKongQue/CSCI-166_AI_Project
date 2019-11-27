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
protected:
    Window* window;
    std::vector<Entity*>* entities;
    std::string currLevel;
    SDL_Texture* levelMsgTexture;
    SDL_Texture* grassTexture;
    SDL_Texture* wallTexture;
    std::vector<int>* walls;
public:
    Display(Window*, std::vector<Entity*>*);
    ~Display();
public:
    virtual void OnRender();
    void LoadLevel(std::string level);
};

#endif /* DISPLAY_H */