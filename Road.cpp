//#include "Road.h"
//Road::Road(vector<int>capacity = { 0,0,0,0,0 }) {
//	this->capacity = capacity;
//}
//bool Road::IsComplete() {
//	if (this->complete)
//		return true;
//	for (int i = 0; i < capacity.size(); i++) {
//		if (capacity[i] < this->config["Costs"]["Road"][i])
//			return false;
//	}
//	for (int i = 0; i < capacity.size(); i++) {
//		capacity[i] -= this->config["Costs"]["Road"][i];
//	}
//	this->complete = true;
//	return true;
//}
//void Road::addResource(int resourceType, int amount) {
//	if (this->capacity[resourceType] + amount > this->config["Capacities"]["Road"][resourceType]) {
//		this->capacity[resourceType] = this->config["Capacities"]["Road"][resourceType];
//	}
//	else {
//		this->capacity[resourceType] += this->config["Capacities"]["Road"][resourceType];
//		this->IsComplete();
//	}
//
//
//
//}