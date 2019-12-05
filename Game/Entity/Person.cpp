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
	vSize(this->window->gridSizeX* this->window->gridSizeY),
	vk(nullptr),
	gamma(0.01f),
	engine(seeder())
{}

float* Person::GetVk() { return nullptr; }
int Person::GetIterNum() { return 3; }

void Person::LoadVk() {
	this->vk = this->GetVk();
	if (this->vk == nullptr) {
		this->vk = new float[this->vSize];
		for (int i = 0; i < this->vSize; i++) {
			this->vk[i] = 0;
		}
	}
}

std::vector<Entity::State*>* Person::GetStates(int pos) {
	std::vector<Entity::State*>* states = new std::vector<Entity::State*>();

	// retrieve all states
	for (int i : {-1, 0, 1}) {
		for (int j : { -1, 0, 1 }) {
			int x = this->GetX(pos) + i;
			int y = this->GetY(pos) + j;

			if (
				((i == 0) != (j == 0))
				&& (x >= 0 && x < this->window->gridSizeX)
				&& (y >= 0 && y < this->window->gridSizeY)
				&& (!this->IsWall(x, y))
			) {
				STATE state = (i == 0 && j == -1) ? STATE::NORTH :
					(i == 1 && j == 0) ? STATE::EAST :
					(i == 0 && j == 1) ? STATE::SOUTH :
					STATE::WEST;
				states->push_back(new Entity::State{
					state,
					this->GetPos(x, y),
					[=]()->void {
						this->posX = x;
						this->posY = y;
					},
					[=]()->int {
						for (Entity* entity : *this->entities) {
							if (entity->posX == x && entity->posY == y)
								return entity->GetReward(this->type);
						}
						return 0;
					}
					});
			}
		}
	}

	return states;
}

std::vector<Entity::State*>* Person::AddStates(int pos) {
	return new std::vector<Entity::State*>();
}
//#include <iostream>
void Person::MakeMove() {
	this->Bellmans();
	this->MaxState();
	/*for (int i = 0; i < this->vSize; i++) {
		if (i % 20 == 0) printf("\n");
		if (this->IsWall(i))
			printf("X");
		else
			std::cout << this->vk[i];
		if (i % 20 != 19) printf(",");
	}
	printf("\n------\n");*/
}

float Person::Equation(Entity::State* state, std::vector<Entity::State*>* states) {
	float t = 0.0f;
	int r = 0;
	float sum = 0.0f;
	for (Entity::State* s : *states) {
		t = (s == state) ? 1 - (0.1 * (states->size() - 1)) : 0.1 * (states->size() - 1);
		r = s->reward();
		sum += (t * (r + (gamma * this->vk[s->pos])));
	}
	return sum;
}

void Person::Bellmans() {
	std::vector<Entity::State*>* states = nullptr;
	std::vector<Entity::State*>* addStates = nullptr;

	// run value iteration
	for (int c = 0; c < this->GetIterNum(); c++) {
		for (int i = 0; i < this->vSize; i++) {
			if (this->IsWall(i)) {
				continue;
			}
			bool found = false;
			for (Entity* entity : *this->entities) {
				int pos = this->GetPos(entity->posX, entity->posY);
				if (entity != this && i == pos) {
					this->vk[i] = entity->GetReward(this->type);
					found = true;
					break;
				}
			}
			if (found) continue;
			states = this->GetStates(i);
			addStates = this->AddStates(i);
			
			states->insert(states->end(), addStates->begin(), addStates->end());
			
			float max = INTMAX_MIN;
			for (Entity::State* state : *states) {
				float val = this->Equation(state, states);
				if (val > max)
					max = val;
			}

			this->vk[i] = max;

			for (Entity::State *state : *states) { delete state; }
			states->clear();
			states->shrink_to_fit();
			addStates->clear();
			addStates->shrink_to_fit();
			delete states;
			delete addStates;
		}
	}
}

void Person::MaxState() {
	std::vector<Entity::State*>* states = this->GetStates(this->GetPos(this->posX, this->posY));
	std::vector<Entity::State*>* addStates = this->AddStates(this->GetPos(this->posX, this->posY));

	states->insert(states->end(), addStates->begin(), addStates->end());

 	Entity::State* maxState = nullptr;
	for (Entity::State* state : *states) {
		if (maxState == nullptr || this->vk[state->pos] > this->vk[maxState->pos]) {
			maxState = state;
		}
	}

	std::vector<Entity::State*>* maxStates = new std::vector<Entity::State*>();
	maxStates->push_back(maxState);
	for (Entity::State* state : *states) {
		if (state != maxState && this->vk[state->pos] == this->vk[maxState->pos])
			maxStates->push_back(state);
	}
	std::uniform_int_distribution<int> nrand(0, maxStates->size() - 1);
	maxState = maxStates->at(nrand(this->engine));
	maxStates->clear();
	maxStates->shrink_to_fit();
	delete maxStates;
	
	maxState->action();

	for (Entity::State* state : *states) {
		delete state;
	}
	states->clear();
	states->shrink_to_fit();
	addStates->clear();
	addStates->shrink_to_fit();
	delete states;
	delete addStates;
}

Person::~Person() {
	//delete[] vk;
}