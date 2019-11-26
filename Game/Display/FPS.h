#pragma once
#ifndef FPS_H
#define FPS_H

#include <SDL.h>

class FPS {
private:
	int oldTime;
	int lastTime;
	int numFrames;
	int frames;
	float speedFactor;
public:
	FPS();
public:
	void OnLoop();
	int GetFPS();
	float GetSpeedFactor();
};

#endif /* FPS_H */