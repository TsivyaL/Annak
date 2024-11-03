#include "Infrastructure.h"
Infrastructure::Infrastructure(string type, vector<int>capacity) {
	this->config = Files::GetConfig();
	this->complete = false;
	this->type = type;
	this->capacity = capacity;

}

bool Infrastructure::IsComplete() {
	if (this->complete)
		return true;
	for (int i = 0; i < capacity.size(); i++) {
		if (capacity[i] < this->config["Costs"][this->type][i].get<int>())
			return false;
	}
	for (int i = 0; i < capacity.size(); i++) {
		capacity[i] -= this->config["Costs"][this->type][i].get<int>();;
	}
	this->complete = true;
	/*if (this->type == "City") {
		world.AddCity();
	}
	else if (this->type == "Village") {
		world.AddVilage();
	}
	else
		world.AddRoad();*/
	return true;
}

void Infrastructure::addResource(int resourceType, int amount) {
	if (this->capacity[resourceType] + amount > this->config["Capacities"][this->type][resourceType]) {
		this->capacity[resourceType] = this->config["Capacities"][this->type][resourceType].get<int>();
	}
	else {
		//cout << this->config["Capacities"][this->type][resourceType].get<int>()<<"\n";
		this->capacity[resourceType] += amount;
		this->IsComplete();
	}



}

string Infrastructure::GetType() {
	return this->type;
}

void Infrastructure::SetComplete() {
	this->complete = true;
}

void Infrastructure::MakeEmpty() {
	this->capacity = { 0,0,0,0,0 };
}

int Infrastructure::GetPeople() {
	return this->capacity[4];
}
vector<int>Infrastructure::GetCapacity() {
	return this->capacity;
}