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

}

float Person::Equation(int* vk_1, Entity::State* state) {
	float gamma = 0.1f;
	for (Entity* entity : *this->entities) {
		if (this->GetPos(entity->posX, entity->posY) == state)
			return transition * (entity->GetReward() + (gamma * vk_1[state]));
	}
	return (transition * (0.0f + (gamma * vk_1[state])));
}

int Person::Bellmans() {
	//int size = (this->window->gridSizeX) * (this->window->gridSizeY);
	int* vk_1 = new int[8] { 0 };
	int* vk = new int[8] { 0 };
	
	std::vector<Entity::State*>* states = this->GetStates();
	std::vector<Entity::State*>* addStates = this->AddStates();
	
	states->insert(states->end(), addStates->begin(), addStates->end());

	for (Entity::State* state : states) {
		this->Equation(vk_1, state);
	}

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
}

std::vector<Entity::State*>* Person::AddStates() {
	return new std::vector<Entity::State*>();
}

Person::~Person() {

}