#include "Game.h"

Game::Game() :
	running(false),
	gameWon(false),
	window(nullptr),
	display(nullptr),
	entities(nullptr)
{}

void Game::LoadLevel(const char* level) {
	std::string line = "";
	std::ifstream file(level);
	int currIndex = 0;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			for (int i = 0; i < line.size(); ++i, ++currIndex) {

				switch (line[i] - '0') {
				case GRID_TYPE::WALL:
					this->display->AddWall(currIndex);
					break;

				case GRID_TYPE::PLAYER:
					this->entities->push_back(new Player(this->window, this->entities, this->display->GetWalls(), currIndex));
					break;

				case GRID_TYPE::GUARD:
					this->entities->push_back(new Guard(this->window, this->entities, this->display->GetWalls(), currIndex));
					break;

				case GRID_TYPE::ARROW:
					this->entities->push_back(new Arrow(this->window, this->entities, this->display->GetWalls(), currIndex));
					break;

				case GRID_TYPE::TREASURE:
					this->entities->push_back(new Treasure(this->window, this->entities, this->display->GetWalls(), currIndex));
					break;

				default:
					break;
				}
			}
		}
	}

}


void Game::OnInit() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}
    this->LoadLevel("./Assets/maps/level_1.txt");
	this->window = new Window();								// Create window
	this->entities = new std::vector<Entity*>();				// Create entity array
	this->display = new Display(this->window);	// Create Displays
	this->running = true;
}

void Game::OnLoop() {
	for (Entity* entity : *this->entities) {
		entity->OnLoop();										// Run each entity loop
	}
}

void Game::OnRender() {
	this->window->ClearScreen();								// Clear the screen
	this->display->OnRender();									// Render Display

	for (Entity* entity : *this->entities) {
		entity->OnRender();										// Render each entity
	}

	this->window->UpdateScreen();								// update the screen with the render at the end
}

void Game::Run() {
	this->OnInit();

	SDL_Event Event;
	while (this->running) {
		while (SDL_PollEvent(&Event)) {
			//User requests quit
			if (Event.type == SDL_QUIT) {
				this->running = false;
			}
		}

		this->OnLoop();
		this->OnRender();
	}
}

Game::~Game() {
	this->running = false;
	this->gameWon = false;
	
	// delete all entity textures
	for (SDL_Texture* texture : Entity::spriteCache) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	Entity::spriteCache.clear();
	Entity::spriteCache.shrink_to_fit();

	// clear, reallocate, and delete entities
	for (Entity* entity : *this->entities) {
		delete entity;
	}
	this->entities->clear();
	this->entities->shrink_to_fit();
	delete this->entities;

	// delete all other pointers
	delete this->display;
	delete this->window;

	// Close SDL
	SDL_Quit();
}