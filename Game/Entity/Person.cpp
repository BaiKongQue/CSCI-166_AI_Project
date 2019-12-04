#include "Person.h"

Person::Person(Window* window,
	std::vector<Entity*>* entities,
	std::vector<int>* walls,
	int spawnPos,
	GRID_TYPE type,
	int numberFrames,
	const char* spritePath
) :
	Entity(window, entities, walls, spawnPos, type, numberFrames, spritePath),
	vSize(5),
	vk_1(new float[this->vSize]),
	vk(new float[this->vSize]),
	gamma(0.01f),
	engine(seeder()),
	vGrid(nullptr)
{

	// fill array with initial values
	for (int i = 0; i < this->vSize; i++) {
		vk_1[i] = 0;
		vk[i] = INTMAX_MIN;
	}
}

float* Person::GetVGrid() {
	return nullptr;
}

void Person::MakeMove() {
	if (this->vGrid == nullptr)
		this->vGrid = this->GetVGrid();
	this->Bellmans();
}

float Person::Equation(Entity::State* state, std::vector<Entity::State*>* states) {
	float t = 0.0f;
	int r = 0;
	float sum = 0.0f;
	for (Entity::State* s : *states) {
		t = (s == state) ? 1 - (0.1 * (states->size() - 1)) : 0.1 * (states->size() - 1);
		r = s->reward();
		sum += (t * (r + (gamma * this->vk_1[state->state] * this->vGrid[state->pos])));
	}
	return sum;
}
//#include <iostream>
//void disp(float* ar) {
//	for (int i = 0; i < 5; i++) {
//		std::cout << (ar[i] < -10000 ? -1111 : ar[i]) << " ";
//	}
//	std::cout << std::endl;
//}
void Person::Bellmans() {
	// fill array with initial values
	for (int i = 0; i < this->vSize; i++) {
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
			this->vk[state->state] = this->Equation(state, states);
			//this->vtest[state->pos] = (this->vtest[state->pos] == 0) ? this->vk[state->state] : this->vk[state->state] * this->vtest[state->pos];
		}
		//for (int i = 0; i < this->vSize; i++) {
		for (Entity::State* state : *states) {
			this->vk_1[state->state] = this->vk[state->state];// *(this->vtest[state->pos] == 0 ? 1 : this->vtest[state->pos]);
		}
	}
		//for (Entity::State* state : *states)
	
	//disp(this->vk);

	Entity::State* maxState = this->MaxState(states);
	maxState->action();
	if (this->vGrid[maxState->pos] == 0)
		printf("A");
	this->vGrid[maxState->pos] = this->gamma * this->vk[maxState->state];
	if (this->vGrid[maxState->pos] == 0)
		printf("a");

	// delete all pointers
	for (Entity::State *state : *states) { delete state; }
	states->clear();
	states->shrink_to_fit();
	delete states;
	addStates->clear();
	addStates->shrink_to_fit();
	delete addStates;

}

Entity::State* Person::MaxState(std::vector<Entity::State*>* states) {
 	Entity::State* maxState = nullptr;
	float maxVal = INTMAX_MIN;
	for (Entity::State* state : *states) {
		if (maxState == nullptr || this->vk[state->state] > maxVal) {
			maxState = state;
			maxVal = this->vk[state->state];
		}
	}

	if (maxState == nullptr) {
		std::uniform_int_distribution<int> nrand(0, states->size() - 1);
		return states->at(nrand(this->engine));
	}

	std::vector<Entity::State*>* maxStates = new std::vector<Entity::State*>();
	maxStates->push_back(maxState);
	for (Entity::State* state : *states) {
		if (this->vk[state->state] == this->vk[maxState->state])
			maxStates->push_back(state);
	}
	std::uniform_int_distribution<int> nrand(0, maxStates->size() - 1);
	maxState = maxStates->at(nrand(this->engine));
	maxStates->clear();
	maxStates->shrink_to_fit();
	delete maxStates;
	return maxState;
}

std::vector<Entity::State*>* Person::AddStates() {
	return new std::vector<Entity::State*>();
}

Person::~Person() {
	delete[] vk;
	delete[] vk_1;
}