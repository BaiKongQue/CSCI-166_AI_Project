#include "Game.h"

Game::Game() :
	running(false),
	gameWon(false),
	window(nullptr),
	display(nullptr),
	entities(nullptr),
	turn(0),
	playerAlive(true)
{}

void Game::LoadLevel(const char* level) {
	this->ClearGame();

	std::string line = "";
	std::ifstream file(level);
	int currIndex = 0;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			for (int i = 0; i < line.size(); ++i) {
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
				if (line[i] != ' ') currIndex++;
			}
		}
	}

}

void Game::ClearGame() {
	this->entities->clear();
	this->entities->shrink_to_fit();
	
	this->display->GetWalls()->clear();
	this->display->GetWalls()->shrink_to_fit();

	this->playerAlive = true;
	this->turn = 0;
	this->gameWon = false;
}


void Game::OnInit() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	this->window = new Window();								// Create window
	this->entities = new std::vector<Entity*>();				// Create entity array
	this->display = new Display(this->window);	// Create Displays
    this->LoadLevel("./Assets/maps/level_2.txt");
	this->running = true;
}

void Game::OnLoop() {
	for (Entity* entity : *this->entities) {
		entity->OnLoop();										// Run each entity loop
	}

	for (int i = 0; i < this->entities->size(); i++) {
		Entity* p = this->entities->at(i);
		if (this->playerAlive && p->type == GRID_TYPE::PLAYER && p->dead) {
			this->playerAlive = false;
			this->gameWon = false;
		}
		if (p->type == GRID_TYPE::TREASURE && p->dead)
			this->gameWon = true;
		if (p->dead) {
			this->entities->erase(this->entities->begin() + i);
			delete p;
		}
	}

	if (this->gameWon && this->playerAlive || !this->playerAlive) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		this->LoadLevel("./Assets/maps/level_2.txt");
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

void Game::TakeTurn() {
	while (this->running) {
		while (this->running && this->playerAlive && !this->gameWon) {
			for (Entity* entity : *this->entities) {
				if (entity->type == GRID_TYPE::PLAYER && this->turn % 2 == 0)
					entity->MakeMove();
				else if (entity->type == GRID_TYPE::GUARD && this->turn % 2 == 1)
					entity->MakeMove();
			}
			this->turn++;
			std::this_thread::sleep_for(std::chrono::milliseconds(30));

		}
	}
}

void Game::Run() {
	this->OnInit();

	SDL_Event Event;
	std::thread TurnThread(&Game::TakeTurn, this);
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
	TurnThread.join();
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