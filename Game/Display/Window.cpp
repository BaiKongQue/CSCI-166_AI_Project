#include "Window.h"

Window::Window() :
	window(nullptr),
	renderer(nullptr),
	font(nullptr),
	fpsControl(nullptr),
	bitSize(32),
	gridSizeX(20),
	gridSizeY(20),
	windowWidth(0),
	windowHeight(0)
{
	this->windowWidth = this->gridSizeX * this->bitSize;
	this->windowHeight = this->gridSizeY * this->bitSize;

	// initialize Window
	this->window = SDL_CreateWindow(
		"CSCI-166 AI Project: Robin  Hood",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		this->windowWidth,
		this->windowHeight,
		SDL_WINDOW_SHOWN
	);
	if (this->window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	// initialize Renderer
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	// initialize Font
	this->font = TTF_OpenFont("FreeSans.ttf", 28);
	if (this->font == nullptr) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}
	
	// initialize Img
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	this->fpsControl = new FPS();
}

SDL_Texture* Window::LoadImageTexture(const char* path) {
	if (!path)
		return nullptr;

	SDL_Surface* tempSurface = IMG_Load(path);
	if (!tempSurface)
		return nullptr;

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	delete tempSurface;

	if (!newTexture)
		return nullptr;

	delete path;
	return newTexture;
}

SDL_Texture* Window::LoadTextTexture(const char* text, SDL_Color textColor = {0,0,0}) {
	if (!text)
		return nullptr;

	SDL_Surface* tempSurface = TTF_RenderText_Blended(this->font, text, textColor);
	if (!tempSurface)
		return nullptr;

	SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	if (!msgTexture)
		return nullptr;

	delete text;
	return msgTexture;
}

void Window::ClearScreen() {
	SDL_RenderClear(this->renderer);
}

void Window::Draw(SDL_Texture* src, SDL_Rect& srcRect, SDL_Rect& destRect) {
	if (!src) {
		printf("Failed rendering image, src is empty!");
		return;
	}

	SDL_RenderCopy(this->renderer, src, &srcRect, &destRect);
}

Window::~Window() {
	// free font
	TTF_CloseFont(this->font);
	delete this->font;

	// destroy window    
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	delete this->renderer;
	delete this->window;

	// Destroy fps controller
	delete this->fpsControl;
}

