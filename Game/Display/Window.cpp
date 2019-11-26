#include "Window.h"

SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;

int Window::bitSize = 32;
int Window::gridSizeX = 20;
int Window::gridSizeY = 20;
int Window::windowWidth = Window::gridSizeX * Window::bitSize;
int Window::windowHeight = Window::gridSizeY * Window::bitSize;

Window::Window() :
	font(nullptr),
	fpsControl(nullptr)
{}

void Window::OnInit() {
	Window::window = SDL_CreateWindow(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		Window::windowWidth,
		Window::windowHeight,
		SDL_WINDOW_SHOWN
	);
	if (Window::window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	Window::renderer = SDL_CreateRenderer(Window::window, -1, SDL_RENDERER_ACCELERATED);
	if (Window::renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}
}