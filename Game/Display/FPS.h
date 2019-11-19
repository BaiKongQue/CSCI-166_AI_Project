#pragma once
#ifndef FPS_H
#define FPS_H

class FPS {
private:
	int oldTime;
	int lastTime;
	int speedFactor;
	int numFrames;
	int frames;
public:
	FPS();
public:
	void OnLoop();
	int GetFPS();
	int GetSpeedFactor();
};

#endif /* FPS_H */