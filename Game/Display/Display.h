#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "../Enum/Display.enum.h"
#include "../Enum/GridType.enum.h"
#include "Window.h"

class Display {
protected:
    static DISPLAY currDisplay;
    Window* window;
public:
    Display(Window*);
    ~Display();
public:
    virtual void OnRender();
    void LoadDisplay(DISPLAY display);
};
#endif /* DISPLAY_H */