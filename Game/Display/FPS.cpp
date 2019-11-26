#include "FPS.h"

FPS::FPS() :
	oldTime(0),
	lastTime(0),
	numFrames(0),
	frames(0),
	speedFactor(0.0f)
{}

void FPS::OnLoop() {
	if (this->oldTime + 1000 < SDL_GetTicks()) {
		this->oldTime = SDL_GetTicks();
		this->numFrames = this->frames;
		this->frames = 0;
	}

	this->speedFactor = ((SDL_GetTicks() - this->lastTime) / 100.0f) * 32.0f;
	this->lastTime = SDL_GetTicks();
	
	this->frames++;
}

int FPS::GetFPS() {
	return this->numFrames;
}

float FPS::GetSpeedFactor() {
	return this->speedFactor;
}