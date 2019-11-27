#include "Display.h"

Display::Display(Window* window, std::vector<Entity*>* entities) :
    window(window),
    walls(nullptr),
    entities(entities),
    levelMsgTexture(nullptr),
    grassTexture(nullptr),
    wallTexture(nullptr)
{
    
}

Display::~Display() {
    
}

void Display::OnRender() {
    
}

void Display::LoadLevel(std::string level) {
    std::string line = "";
    std::ifstream file(level);
    int currIndex = 0;
       
    if (file.is_open()) {
        while (std::getline(file, line)) {
            for (int i = 0; i < line.size(); ++i, ++currIndex) {
                
                switch (line[i]) {
                    case GRID_TYPE::WALL:
                        this->walls->push_back(currIndex);
                        break;
                        
                    case GRID_TYPE::PLAYER:
                        this->entities->push_back(new Player(currIndex));
                        break;
                    
                    case GRID_TYPE::GUARD:
                        this->entities->push_back(new Guard(currIndex));
                        break;
                    
                    case GRID_TYPE::ARROW:
                        this->entities->push_back(new Arrow(currIndex));
                        break;
                    
                    case GRID_TYPE::TREASURE:
                        this->entities->push_back(new Treasure(currIndex));
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }
    
}
