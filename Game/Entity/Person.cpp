#include "Person.h"

Person::Person(Window* window,
	std::vector<Entity*>* entities,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	Entity(window, entities, walls, spawnPos, type, numberFrames, spritePath)
{}

void Person::die() {
	this->dead = true;
}

void Person::OnMove(int newX, int newY) {
	if (this->CanMove(newX, newY)) {
		this->posX = newX;
		this->posY = newY;
	}
}

bool Person::CanMove(int newX, int newY) {
	return !this->IsWall(newX, newY);
}

void Person::MakeMove() {
	this->Bellmans();
}

float Person::Equation(float* vk_1, Entity::State* state, std::vector<Entity::State*>* states) {
	float gamma = 0.1f;
	float t = 0.0f;
	int r = 0;
	float sum = 0.0f;
	for (Entity::State* s : *states) {
		t = (s == state) ? 1 - (0.1 * (states->size() - 1)) : 0.1 * (states->size() - 1);
		r = s->reward();
		sum += (t * (r + (gamma * vk_1[state->state])));
	}
	return sum;
}

STATE Person::Bellmans() {
	int size = 8;
	float* vk_1 = new float[size];
	float* vk = new float[size];
	
	// fill array with initial values
	for (int i = 0; i < size; i++) {
		vk_1[i] = 0;
		vk[i] = INTMAX_MIN;
	}

	// get all states
	std::vector<Entity::State*>* states = this->GetStates();
	std::vector<Entity::State*>* addStates = this->AddStates();
	
	states->insert(states->end(), addStates->begin(), addStates->end());

	// run value iteration
	for (int i = 0; i < 4; i++) {
		for (Entity::State* state : *states) {
			vk[state->state] = this->Equation(vk_1, state, states);
		}
		for (int i = 0; i < size; i++)
			vk_1[i] = vk[i];
	}

	STATE maxState = this->MaxState(vk, size);

	// delete all pointers
	for (Entity::State *state : *states) {
		delete state;
	}
	states->clear();
	states->shrink_to_fit();
	delete states;
	addStates->clear();
	addStates->shrink_to_fit();
	delete addStates;
	delete[] vk;
	delete[] vk_1;
	return maxState;
}

STATE Person::MaxState(float* ar, int size) {
 	int maxState = -1;
	float maxVal = INTMAX_MIN;
	for (int i = 0; i < size; i++) {
		if (ar[i] > maxVal) {
			maxState = i;
			maxVal = ar[i];
		}
	}
	return static_cast<STATE>(maxState);
}

std::vector<Entity::State*>* Person::AddStates() {
	return new std::vector<Entity::State*>();
}

Person::~Person() {

}