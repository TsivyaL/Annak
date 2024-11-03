#include "Mover.h"
Mover::Mover(string type, vector<int>capacity) {
	this->type = type;
	this->resource = capacity;
}
void Mover::TakeResources() {
	
}
string Mover::GetType() {
	return this->type;
}
void Mover::MakeEmpty() {
	this->resource = { 0,0,0,0,0 };
}
vector<int> Mover::GetResorces() {
	return this->resource;
}

void Mover::AddResource(int type, int amount) {
	if (this->resource[type] + amount > Files::GetConfig()["Capacities"][this->type][type])
		this->resource[type] = Files::GetConfig()["Capacities"][this->type][type];
	else
		this->resource[type] += amount;
}
