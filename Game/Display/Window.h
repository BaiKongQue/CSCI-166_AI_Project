#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "FPS.h"
#include <string>

static class Window {
private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
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
	void OnInit();
	void OnRender();
	void OnCleanup();
	static SDL_Texture* LoadTexture(const std::string& path);
};

#endif /* WINDOW_H */