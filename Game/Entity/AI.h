#pragma once
#ifndef AI_H
#define AI_H

class AI {
protected:
	float transition;
	int** cache;
public:
	AI();
private:
	float Sample();
	float GetReward();
protected:
	void Bellmans();
	float Equation();
};

#endif /* AI_H */