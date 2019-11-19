#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "../Enum/Display.enum.h"
#include "../Enum/GridType.enum.h"
#include "Window.h"

class Display {
protected:
	static DISPLAY currDisplay;
	static int* grid;
public:
	Display();
public:
	void OnInit();
	void OnRender();
	void LoadDisplay(DISPLAY display);
	void OnCleanup();
};

#endif /* DISPLAY_H */