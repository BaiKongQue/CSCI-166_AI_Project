#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "FPS.h"

class Window {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	TTF_Font* font;
	FPS* fpsControl;
	int windowWidth;
	int windowHeight;
	int bitSize;
	int gridSizeX;
	int gridSizeY;
public: 
	Window();
public:
	SDL_Texture* LoadImageTexture(const char* path);
	SDL_Texture* LoadTextTexture(const char* text, SDL_Color textColor);
	void ClearScreen();
	void Draw(SDL_Texture* src, SDL_Rect& srcRect, SDL_Rect& destRect);
public:
	~Window();
};

#endif /* WINDOW_H */