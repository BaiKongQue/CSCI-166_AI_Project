#pragma once
#ifndef AI_H
#define AI_H

class AI {
protected:
	float transition;
	float reward;
	int** cache;
public:
	AI();
private:
	float Sample();
protected:
	void Bellmans();
	float Equation();
public:
	float GetReward();
public:
	~AI();
};

#endif /* AI_H */