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
    
}

Display::~Display() {
    
}