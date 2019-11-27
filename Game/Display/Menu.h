#pragma once
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "Display.h"

class Menu : public Display {
private:
	SDL_Texture* displayTexture;
public:
	Menu();
private:
	void LoadMenuTexture();
};

#endif /* MENU_H */