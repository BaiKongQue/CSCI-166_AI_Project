#include "Display.h"

Display::Display(Window* window) :
    window(window),
    walls(nullptr),
    levelMsgTexture(nullptr),
    grassTexture(nullptr),
    wallTexture(nullptr)
{
	this->walls = new std::vector<int>();
}

std::vector<int>* Display::GetWalls() {
	return this->walls;
}

void Display::AddWall(int pos) {
    this->walls->push_back(pos);
}

void Display::ClearWalls() {
    this->walls->clear();
    this->walls->shrink_to_fit();
}

void Display::OnRender() {
    int size = this->window->gridSizeY * this->window->gridSizeX;
    SDL_Rect* currRect = new SDL_Rect{0, 0, this->window->bitSize, this->window->bitSize};
    int currWall = 0;
    
    for (int i = 0; i < size; ++i) {
        int x = i % this->window->gridSizeX;
        int y = i / this->window->gridSizeY;
        currRect->x = x;
        currRect->y = y;
        if (i == this->walls->at(currWall)) {
            this->window->Draw(this->wallTexture, currRect, nullptr);
            ++currWall;
        }
        else {
            this->window->Draw(this->grassTexture, currRect, nullptr);
        }
        
    }

    delete currRect;
}

Display::~Display() {
    this->ClearWalls();
    delete this->walls;
    SDL_DestroyTexture(levelMsgTexture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(wallTexture);
    levelMsgTexture = grassTexture = wallTexture = nullptr;
}