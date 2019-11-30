#include "Display.h"

Display::Display(Window* window, std::vector<Entity*>* entities) :
    window(window),
    walls(nullptr),
    entities(entities),
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
    std::vector<SDL_Rect*>* rects = new std::vector<SDL_Rect*>();
    int currWall = 0;
    
    for (int i = 0; i < size; ++i) {
        int x = this->walls->at(i) % this->window->gridSizeX;
        int y = this->walls->at(i) / this->window->gridSizeY;
        rects->push_back(new SDL_Rect{x, y, this->window->bitSize, this->window->bitSize});
        if (i == this->walls->at(currWall)) {
            this->window->Draw(this->wallTexture, rects->at(i), rects->at(i));
            ++currWall;
        }
        else {
            this->window->Draw(this->grassTexture, rects->at(i), rects->at(i));
        }
    }
    
    for (int i = 0; i < this->entities->size(); ++i) {
        this->entities->at(i)->OnRender();
    }
    
    for (int i = 0; i < rects->size(); ++i) {
        delete rects->at(i);
    }
    rects->clear();
    rects->shrink_to_fit();
    delete rects;
}

Display::~Display() {
    this->ClearWalls();
    delete this->walls;
    SDL_DestroyTexture(levelMsgTexture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(wallTexture);
    levelMsgTexture = grassTexture = wallTexture = nullptr;
}