#include "Display.h"

Display::Display(Window* window) :
    window(window),
    walls(nullptr),
    levelMsgTexture(nullptr),
    grassTexture(nullptr),
    wallTexture(nullptr),
	currRect(new SDL_Rect{ 0, 0, this->window->bitSize, this->window->bitSize })
{
	this->walls = new std::vector<int>();
    this->wallTexture = this->window->LoadImageTexture("./Assets/images/wall_texture.png");
    this->grassTexture = this->window->LoadImageTexture("./Assets/images/grass_texture.png");
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
    int currWall = 0;
    
    for (int i = 0; i < size; ++i) {
        currRect->x = (i % this->window->gridSizeX) * this->window->bitSize;
        currRect->y = (i / this->window->gridSizeY) * this->window->bitSize;
        if (currWall < this->walls->size() && i == this->walls->at(currWall)) {
            this->window->Draw(this->wallTexture, currRect, nullptr);
            ++currWall;
        } else {
            this->window->Draw(this->grassTexture, currRect, nullptr);
        }
        
    }

}

Display::~Display() {
    delete this->currRect;
    this->ClearWalls();
    delete this->walls;
    SDL_DestroyTexture(levelMsgTexture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(wallTexture);
    levelMsgTexture = grassTexture = wallTexture = nullptr;
}