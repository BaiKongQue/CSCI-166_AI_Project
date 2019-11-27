#include "Map.h"

Map::Map(Window* window) :
    Display(window),
    levelMsgTexture(nullptr),
    grassTexture(nullptr),
    wallTexture(nullptr)
{
    levelMsgTexture = window->LoadImageTexture("");
    grassTexture = window->LoadImageTexture("");
    wallTexture = window->LoadImageTexture("");
}

void Map::LoadLevel(std::string level) {
    std::string line = "";
    std::ifstream file(level);
    int currIndex = 0;
       
    if (file.is_open()) {
        while (std::getline(file, line)) {
            for (int i = 0; i < line.size(); ++i, ++currIndex) {
                
                switch (line[i]) {
                    case GRID_TYPE::WALL:
                        this->walls.push_back(currIndex);
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
    
}