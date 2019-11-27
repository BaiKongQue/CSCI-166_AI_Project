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

				switch (line[i]) {
				case GRID_TYPE::WALL:
					this->display->AddWall(currIndex);
					break;

				case GRID_TYPE::PLAYER:
					this->entities->push_back(new Player(this->window, this->display->GetWalls(), currIndex));
					break;

				case GRID_TYPE::GUARD:
					this->entities->push_back(new Guard(this->window, this->display->GetWalls(), currIndex));
					break;

				case GRID_TYPE::ARROW:
					this->entities->push_back(new Arrow(this->window, this->display->GetWalls(), currIndex));
					break;

				case GRID_TYPE::TREASURE:
					this->entities->push_back(new Treasure(this->window, this->display->GetWalls(), currIndex));
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

	this->window = new Window();								// Create window
	this->entities = new std::vector<Entity*>();				// Create entity array
	this->display = new Display(this->window, this->entities);	// Create Displays
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
}

void Game::Run() {
	this->OnInit();

	while (this->running) {
		while (SDL_PollEvent(&this->events) != 0) {
			//User requests quit
			if (this->events.type == SDL_QUIT) {
				this->running = false;
			}
		}

		this->OnLoop();
		this->OnRender();
	}
}

Game::~Game() {
	// clear, reallocate, and delete entities
	this->entities->clear();
	this->entities->shrink_to_fit();
	delete this->entities;

	// delete all other pointers
	delete this->display;
	delete this->window;

	// Close SDL
	SDL_Quit();
}